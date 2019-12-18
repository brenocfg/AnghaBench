#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/  mficmd_frame_tag; } ;
struct mrsas_mfi_cmd {void* frame_mem; int /*<<< orphan*/  frame_phys_addr; int /*<<< orphan*/  frame_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  MRSAS_MFI_FRAME_SIZE ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrsas_alloc_cb ; 

void   *
mrsas_alloc_frame(struct mrsas_softc *sc, struct mrsas_mfi_cmd *cmd)
{
	u_int32_t frame_size = MRSAS_MFI_FRAME_SIZE;

	if (bus_dmamem_alloc(sc->mficmd_frame_tag, (void **)&cmd->frame_mem,
	    BUS_DMA_NOWAIT, &cmd->frame_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot alloc MFI frame memory\n");
		return (NULL);
	}
	if (bus_dmamap_load(sc->mficmd_frame_tag, cmd->frame_dmamap,
	    cmd->frame_mem, frame_size, mrsas_alloc_cb,
	    &cmd->frame_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load IO request memory\n");
		return (NULL);
	}
	return (cmd->frame_mem);
}