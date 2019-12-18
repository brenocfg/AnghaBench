#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union mfi_sgl {TYPE_4__* sg64; TYPE_3__* sg32; TYPE_1__* sg_skinny; } ;
struct mfi_softc {int mfi_flags; int mfi_sge_size; int /*<<< orphan*/  mfi_io_lock; int /*<<< orphan*/  mfi_buffer_dmat; } ;
struct mfi_sg_skinny {int dummy; } ;
struct mfi_frame_header {scalar_t__ cmd; int flags; int sg_count; } ;
struct mfi_command {int cm_error; int cm_stp_len; int cm_flags; int cm_total_frame_size; int cm_extra_frames; int /*<<< orphan*/  cm_dmamap; TYPE_2__* cm_frame; union mfi_sgl* cm_sg; struct mfi_softc* cm_sc; } ;
struct TYPE_11__ {int ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_5__ bus_dma_segment_t ;
struct TYPE_10__ {int len; scalar_t__ addr; } ;
struct TYPE_9__ {int len; scalar_t__ addr; } ;
struct TYPE_8__ {struct mfi_frame_header header; } ;
struct TYPE_7__ {int len; scalar_t__ flag; scalar_t__ addr; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int MFI_CMD_DATAIN ; 
 int MFI_CMD_DATAOUT ; 
 scalar_t__ MFI_CMD_LD_READ ; 
 scalar_t__ MFI_CMD_LD_WRITE ; 
 int MFI_CMD_MAPPED ; 
 scalar_t__ MFI_CMD_PD_SCSI_IO ; 
 scalar_t__ MFI_CMD_STP ; 
 int MFI_FLAGS_SG64 ; 
 int MFI_FLAGS_SKINNY ; 
 int MFI_FRAME_DIR_READ ; 
 int MFI_FRAME_DIR_WRITE ; 
 int MFI_FRAME_IEEE_SGL ; 
 int MFI_FRAME_SGL64 ; 
 int MFI_FRAME_SIZE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfi_complete (struct mfi_softc*,struct mfi_command*) ; 
 int mfi_send_frame (struct mfi_softc*,struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
mfi_data_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct mfi_frame_header *hdr;
	struct mfi_command *cm;
	union mfi_sgl *sgl;
	struct mfi_softc *sc;
	int i, j, first, dir;
	int sge_size, locked;

	cm = (struct mfi_command *)arg;
	sc = cm->cm_sc;
	hdr = &cm->cm_frame->header;
	sgl = cm->cm_sg;

	/*
	 * We need to check if we have the lock as this is async
	 * callback so even though our caller mfi_mapcmd asserts
	 * it has the lock, there is no guarantee that hasn't been
	 * dropped if bus_dmamap_load returned prior to our
	 * completion.
	 */
	if ((locked = mtx_owned(&sc->mfi_io_lock)) == 0)
		mtx_lock(&sc->mfi_io_lock);

	if (error) {
		printf("error %d in callback\n", error);
		cm->cm_error = error;
		mfi_complete(sc, cm);
		goto out;
	}
	/* Use IEEE sgl only for IO's on a SKINNY controller
	 * For other commands on a SKINNY controller use either
	 * sg32 or sg64 based on the sizeof(bus_addr_t).
	 * Also calculate the total frame size based on the type
	 * of SGL used.
	 */
	if (((cm->cm_frame->header.cmd == MFI_CMD_PD_SCSI_IO) ||
	    (cm->cm_frame->header.cmd == MFI_CMD_LD_READ) ||
	    (cm->cm_frame->header.cmd == MFI_CMD_LD_WRITE)) &&
	    (sc->mfi_flags & MFI_FLAGS_SKINNY)) {
		for (i = 0; i < nsegs; i++) {
			sgl->sg_skinny[i].addr = segs[i].ds_addr;
			sgl->sg_skinny[i].len = segs[i].ds_len;
			sgl->sg_skinny[i].flag = 0;
		}
		hdr->flags |= MFI_FRAME_IEEE_SGL | MFI_FRAME_SGL64;
		sge_size = sizeof(struct mfi_sg_skinny);
		hdr->sg_count = nsegs;
	} else {
		j = 0;
		if (cm->cm_frame->header.cmd == MFI_CMD_STP) {
			first = cm->cm_stp_len;
			if ((sc->mfi_flags & MFI_FLAGS_SG64) == 0) {
				sgl->sg32[j].addr = segs[0].ds_addr;
				sgl->sg32[j++].len = first;
			} else {
				sgl->sg64[j].addr = segs[0].ds_addr;
				sgl->sg64[j++].len = first;
			}
		} else
			first = 0;
		if ((sc->mfi_flags & MFI_FLAGS_SG64) == 0) {
			for (i = 0; i < nsegs; i++) {
				sgl->sg32[j].addr = segs[i].ds_addr + first;
				sgl->sg32[j++].len = segs[i].ds_len - first;
				first = 0;
			}
		} else {
			for (i = 0; i < nsegs; i++) {
				sgl->sg64[j].addr = segs[i].ds_addr + first;
				sgl->sg64[j++].len = segs[i].ds_len - first;
				first = 0;
			}
			hdr->flags |= MFI_FRAME_SGL64;
		}
		hdr->sg_count = j;
		sge_size = sc->mfi_sge_size;
	}

	dir = 0;
	if (cm->cm_flags & MFI_CMD_DATAIN) {
		dir |= BUS_DMASYNC_PREREAD;
		hdr->flags |= MFI_FRAME_DIR_READ;
	}
	if (cm->cm_flags & MFI_CMD_DATAOUT) {
		dir |= BUS_DMASYNC_PREWRITE;
		hdr->flags |= MFI_FRAME_DIR_WRITE;
	}
	bus_dmamap_sync(sc->mfi_buffer_dmat, cm->cm_dmamap, dir);
	cm->cm_flags |= MFI_CMD_MAPPED;

	/*
	 * Instead of calculating the total number of frames in the
	 * compound frame, it's already assumed that there will be at
	 * least 1 frame, so don't compensate for the modulo of the
	 * following division.
	 */
	cm->cm_total_frame_size += (sc->mfi_sge_size * nsegs);
	cm->cm_extra_frames = (cm->cm_total_frame_size - 1) / MFI_FRAME_SIZE;

	if ((error = mfi_send_frame(sc, cm)) != 0) {
		printf("error %d in callback from mfi_send_frame\n", error);
		cm->cm_error = error;
		mfi_complete(sc, cm);
		goto out;
	}

out:
	/* leave the lock in the state we found it */
	if (locked == 0)
		mtx_unlock(&sc->mfi_io_lock);

	return;
}