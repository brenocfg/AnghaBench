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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {int /*<<< orphan*/  node; TYPE_1__ tx; } ;
struct virt_dma_chan {int /*<<< orphan*/  (* desc_free ) (struct virt_dma_desc*) ;int /*<<< orphan*/  desc_allocated; } ;

/* Variables and functions */
 scalar_t__ dmaengine_desc_test_reuse (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct virt_dma_desc*) ; 
 struct virt_dma_chan* to_virt_chan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vchan_vdesc_fini(struct virt_dma_desc *vd)
{
	struct virt_dma_chan *vc = to_virt_chan(vd->tx.chan);

	if (dmaengine_desc_test_reuse(&vd->tx))
		list_add(&vd->node, &vc->desc_allocated);
	else
		vc->desc_free(vd);
}