#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int context; } ;
union mfi_frame {TYPE_1__ header; } ;
struct mfi_softc {int mfi_max_fw_cmds; int mfi_cmd_size; struct mfi_command* mfi_commands; int /*<<< orphan*/  mfi_buffer_dmat; int /*<<< orphan*/  mfi_dev; int /*<<< orphan*/  mfi_io_lock; scalar_t__ mfi_sense_busaddr; int /*<<< orphan*/ * mfi_sense; scalar_t__ mfi_frames_busaddr; scalar_t__ mfi_frames; } ;
struct mfi_command {int cm_index; int /*<<< orphan*/  cm_dmamap; struct mfi_softc* cm_sc; scalar_t__ cm_sense_busaddr; int /*<<< orphan*/ * cm_sense; union mfi_frame* cm_frame; scalar_t__ cm_frame_busaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MFI_SENSE_LEN ; 
 int /*<<< orphan*/  M_MFIBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  free (struct mfi_command*,int /*<<< orphan*/ ) ; 
 struct mfi_command* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfi_release_command (struct mfi_command*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_alloc_commands(struct mfi_softc *sc)
{
	struct mfi_command *cm;
	int i, j;

	/*
	 * XXX Should we allocate all the commands up front, or allocate on
	 * demand later like 'aac' does?
	 */
	sc->mfi_commands = malloc(sizeof(sc->mfi_commands[0]) *
	    sc->mfi_max_fw_cmds, M_MFIBUF, M_WAITOK | M_ZERO);

	for (i = 0; i < sc->mfi_max_fw_cmds; i++) {
		cm = &sc->mfi_commands[i];
		cm->cm_frame = (union mfi_frame *)((uintptr_t)sc->mfi_frames +
		    sc->mfi_cmd_size * i);
		cm->cm_frame_busaddr = sc->mfi_frames_busaddr +
		    sc->mfi_cmd_size * i;
		cm->cm_frame->header.context = i;
		cm->cm_sense = &sc->mfi_sense[i];
		cm->cm_sense_busaddr= sc->mfi_sense_busaddr + MFI_SENSE_LEN * i;
		cm->cm_sc = sc;
		cm->cm_index = i;
		if (bus_dmamap_create(sc->mfi_buffer_dmat, 0,
		    &cm->cm_dmamap) == 0) {
			mtx_lock(&sc->mfi_io_lock);
			mfi_release_command(cm);
			mtx_unlock(&sc->mfi_io_lock);
		} else {
			device_printf(sc->mfi_dev, "Failed to allocate %d "
			   "command blocks, only allocated %d\n",
			    sc->mfi_max_fw_cmds, i - 1);
			for (j = 0; j < i; j++) {
				cm = &sc->mfi_commands[i];
				bus_dmamap_destroy(sc->mfi_buffer_dmat,
				    cm->cm_dmamap);
			}
			free(sc->mfi_commands, M_MFIBUF);
			sc->mfi_commands = NULL;

			return (ENOMEM);
		}
	}

	return (0);
}