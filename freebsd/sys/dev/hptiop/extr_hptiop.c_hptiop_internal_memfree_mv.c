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
struct hpt_iop_hba {scalar_t__ ctlcfg_dmat; int /*<<< orphan*/  ctlcfg_dmamap; int /*<<< orphan*/  ctlcfg_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hptiop_internal_memfree_mv(struct hpt_iop_hba *hba)
{
	if (hba->ctlcfg_dmat) {
		bus_dmamap_unload(hba->ctlcfg_dmat, hba->ctlcfg_dmamap);
		bus_dmamem_free(hba->ctlcfg_dmat,
					hba->ctlcfg_ptr, hba->ctlcfg_dmamap);
		bus_dma_tag_destroy(hba->ctlcfg_dmat);
	}

	return 0;
}