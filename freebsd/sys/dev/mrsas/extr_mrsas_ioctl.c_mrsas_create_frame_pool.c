#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; struct mrsas_mfi_cmd** mfi_cmd_list; int /*<<< orphan*/  mficmd_frame_tag; int /*<<< orphan*/  mrsas_parent_tag; } ;
struct mrsas_mfi_cmd {TYPE_2__* frame; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {scalar_t__ pad_0; int /*<<< orphan*/  context; } ;
struct TYPE_5__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int MRSAS_MAX_MFI_CMDS ; 
 int /*<<< orphan*/  MRSAS_MFI_FRAME_SIZE ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mrsas_alloc_frame (struct mrsas_softc*,struct mrsas_mfi_cmd*) ; 

__attribute__((used)) static int
mrsas_create_frame_pool(struct mrsas_softc *sc)
{
	int i;
	struct mrsas_mfi_cmd *cmd;

	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    1, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    MRSAS_MFI_FRAME_SIZE,
	    1,
	    MRSAS_MFI_FRAME_SIZE,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->mficmd_frame_tag)) {
		device_printf(sc->mrsas_dev, "Cannot create MFI frame tag\n");
		return (ENOMEM);
	}
	for (i = 0; i < MRSAS_MAX_MFI_CMDS; i++) {
		cmd = sc->mfi_cmd_list[i];
		cmd->frame = mrsas_alloc_frame(sc, cmd);
		if (cmd->frame == NULL) {
			device_printf(sc->mrsas_dev, "Cannot alloc MFI frame memory\n");
			return (ENOMEM);
		}
		/*
		 * For MFI controllers.
		 * max_num_sge = 60
		 * max_sge_sz  = 16 byte (sizeof megasas_sge_skinny)
		 * Totl 960 byte (15 MFI frame of 64 byte)
		 *
		 * Fusion adapter require only 3 extra frame.
		 * max_num_sge = 16 (defined as MAX_IOCTL_SGE)
		 * max_sge_sz  = 12 byte (sizeof  megasas_sge64)
		 * Total 192 byte (3 MFI frame of 64 byte)
		 */
		memset(cmd->frame, 0, MRSAS_MFI_FRAME_SIZE);
		cmd->frame->io.context = cmd->index;
		cmd->frame->io.pad_0 = 0;
	}

	return (0);
}