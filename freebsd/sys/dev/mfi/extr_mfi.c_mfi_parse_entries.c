#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  evt_class; int /*<<< orphan*/  locale; scalar_t__ reserved; } ;
union mfi_evt {int word; TYPE_1__ members; } ;
typedef  int uint32_t ;
struct mfi_softc {int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/  mfi_buffer_dmat; int /*<<< orphan*/  mfi_io_lock; } ;
struct mfi_evt_list {int count; TYPE_4__* event; } ;
struct mfi_evt_detail {int dummy; } ;
struct TYPE_7__ {int data_len; scalar_t__ cmd_status; scalar_t__ timeout; int /*<<< orphan*/  cmd; } ;
struct mfi_dcmd_frame {TYPE_3__ header; int /*<<< orphan*/  sgl; int /*<<< orphan*/  mbox; int /*<<< orphan*/  opcode; } ;
struct mfi_command {int cm_flags; int cm_len; int /*<<< orphan*/  cm_dmamap; struct mfi_evt_list* cm_data; int /*<<< orphan*/  cm_total_frame_size; int /*<<< orphan*/ * cm_sg; TYPE_2__* cm_frame; } ;
struct TYPE_8__ {int seq; } ;
struct TYPE_6__ {struct mfi_dcmd_frame dcmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int MAX_EVENTS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MFI_CMD_DATAIN ; 
 int /*<<< orphan*/  MFI_CMD_DCMD ; 
 int MFI_CMD_POLLED ; 
 int /*<<< orphan*/  MFI_DCMD_CTRL_EVENT_GET ; 
 int /*<<< orphan*/  MFI_DCMD_FRAME_SIZE ; 
 int /*<<< orphan*/  MFI_MBOX_SIZE ; 
 scalar_t__ MFI_STAT_NOT_FOUND ; 
 scalar_t__ MFI_STAT_OK ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct mfi_evt_list*,int /*<<< orphan*/ ) ; 
 struct mfi_evt_list* malloc (int,int /*<<< orphan*/ ,int) ; 
 struct mfi_command* mfi_dequeue_free (struct mfi_softc*) ; 
 int /*<<< orphan*/  mfi_event_class ; 
 int /*<<< orphan*/  mfi_event_locale ; 
 int mfi_mapcmd (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mfi_queue_evt (struct mfi_softc*,TYPE_4__*) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mfi_parse_entries(struct mfi_softc *sc, int start_seq, int stop_seq)
{
	struct mfi_command *cm;
	struct mfi_dcmd_frame *dcmd;
	struct mfi_evt_list *el;
	union mfi_evt class_locale;
	int error, i, seq, size;

	mtx_assert(&sc->mfi_io_lock, MA_OWNED);

	class_locale.members.reserved = 0;
	class_locale.members.locale = mfi_event_locale;
	class_locale.members.evt_class  = mfi_event_class;

	size = sizeof(struct mfi_evt_list) + sizeof(struct mfi_evt_detail)
		* (MAX_EVENTS - 1);
	el = malloc(size, M_MFIBUF, M_NOWAIT | M_ZERO);
	if (el == NULL)
		return (ENOMEM);

	for (seq = start_seq;;) {
		if ((cm = mfi_dequeue_free(sc)) == NULL) {
			free(el, M_MFIBUF);
			return (EBUSY);
		}

		dcmd = &cm->cm_frame->dcmd;
		bzero(dcmd->mbox, MFI_MBOX_SIZE);
		dcmd->header.cmd = MFI_CMD_DCMD;
		dcmd->header.timeout = 0;
		dcmd->header.data_len = size;
		dcmd->opcode = MFI_DCMD_CTRL_EVENT_GET;
		((uint32_t *)&dcmd->mbox)[0] = seq;
		((uint32_t *)&dcmd->mbox)[1] = class_locale.word;
		cm->cm_sg = &dcmd->sgl;
		cm->cm_total_frame_size = MFI_DCMD_FRAME_SIZE;
		cm->cm_flags = MFI_CMD_DATAIN | MFI_CMD_POLLED;
		cm->cm_data = el;
		cm->cm_len = size;

		if ((error = mfi_mapcmd(sc, cm)) != 0) {
			device_printf(sc->mfi_dev,
			    "Failed to get controller entries\n");
			mfi_release_command(cm);
			break;
		}

		bus_dmamap_sync(sc->mfi_buffer_dmat, cm->cm_dmamap,
		    BUS_DMASYNC_POSTREAD);
		bus_dmamap_unload(sc->mfi_buffer_dmat, cm->cm_dmamap);

		if (dcmd->header.cmd_status == MFI_STAT_NOT_FOUND) {
			mfi_release_command(cm);
			break;
		}
		if (dcmd->header.cmd_status != MFI_STAT_OK) {
			device_printf(sc->mfi_dev,
			    "Error %d fetching controller entries\n",
			    dcmd->header.cmd_status);
			mfi_release_command(cm);
			error = EIO;
			break;
		}
		mfi_release_command(cm);

		for (i = 0; i < el->count; i++) {
			/*
			 * If this event is newer than 'stop_seq' then
			 * break out of the loop.  Note that the log
			 * is a circular buffer so we have to handle
			 * the case that our stop point is earlier in
			 * the buffer than our start point.
			 */
			if (el->event[i].seq >= stop_seq) {
				if (start_seq <= stop_seq)
					break;
				else if (el->event[i].seq < start_seq)
					break;
			}
			mfi_queue_evt(sc, &el->event[i]);
		}
		seq = el->event[el->count - 1].seq + 1;
	}

	free(el, M_MFIBUF);
	return (error);
}