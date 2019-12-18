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
struct mrsas_softc {int /*<<< orphan*/  mficmd_frame_tag; } ;
struct mrsas_mfi_cmd {int /*<<< orphan*/  frame_dmamap; int /*<<< orphan*/ * frame_mem; scalar_t__ frame_phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrsas_free_frame(struct mrsas_softc *sc, struct mrsas_mfi_cmd *cmd)
{
	if (cmd->frame_phys_addr)
		bus_dmamap_unload(sc->mficmd_frame_tag, cmd->frame_dmamap);
	if (cmd->frame_mem != NULL)
		bus_dmamem_free(sc->mficmd_frame_tag, cmd->frame_mem, cmd->frame_dmamap);
}