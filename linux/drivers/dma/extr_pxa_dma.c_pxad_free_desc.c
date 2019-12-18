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
struct virt_dma_desc {int dummy; } ;
struct pxad_desc_sw {int nb_desc; TYPE_1__** hw_desc; int /*<<< orphan*/  desc_pool; int /*<<< orphan*/  first; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  ddadr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pxad_desc_sw*) ; 
 struct pxad_desc_sw* to_pxad_sw_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void pxad_free_desc(struct virt_dma_desc *vd)
{
	int i;
	dma_addr_t dma;
	struct pxad_desc_sw *sw_desc = to_pxad_sw_desc(vd);

	BUG_ON(sw_desc->nb_desc == 0);
	for (i = sw_desc->nb_desc - 1; i >= 0; i--) {
		if (i > 0)
			dma = sw_desc->hw_desc[i - 1]->ddadr;
		else
			dma = sw_desc->first;
		dma_pool_free(sw_desc->desc_pool,
			      sw_desc->hw_desc[i], dma);
	}
	sw_desc->nb_desc = 0;
	kfree(sw_desc);
}