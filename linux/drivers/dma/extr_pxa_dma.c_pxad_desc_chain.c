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
struct pxad_desc_sw {int nb_desc; TYPE_1__** hw_desc; int /*<<< orphan*/  first; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  ddadr; } ;

/* Variables and functions */
 struct pxad_desc_sw* to_pxad_sw_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void pxad_desc_chain(struct virt_dma_desc *vd1,
				struct virt_dma_desc *vd2)
{
	struct pxad_desc_sw *desc1 = to_pxad_sw_desc(vd1);
	struct pxad_desc_sw *desc2 = to_pxad_sw_desc(vd2);
	dma_addr_t dma_to_chain;

	dma_to_chain = desc2->first;
	desc1->hw_desc[desc1->nb_desc - 1]->ddadr = dma_to_chain;
}