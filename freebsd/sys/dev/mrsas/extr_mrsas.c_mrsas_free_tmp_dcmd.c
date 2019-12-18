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
struct mrsas_tmp_dcmd {int /*<<< orphan*/ * tmp_dcmd_tag; int /*<<< orphan*/  tmp_dcmd_dmamap; int /*<<< orphan*/ * tmp_dcmd_mem; scalar_t__ tmp_dcmd_phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrsas_free_tmp_dcmd(struct mrsas_tmp_dcmd *tmp)
{
	if (tmp->tmp_dcmd_phys_addr)
		bus_dmamap_unload(tmp->tmp_dcmd_tag, tmp->tmp_dcmd_dmamap);
	if (tmp->tmp_dcmd_mem != NULL)
		bus_dmamem_free(tmp->tmp_dcmd_tag, tmp->tmp_dcmd_mem, tmp->tmp_dcmd_dmamap);
	if (tmp->tmp_dcmd_tag != NULL)
		bus_dma_tag_destroy(tmp->tmp_dcmd_tag);
}