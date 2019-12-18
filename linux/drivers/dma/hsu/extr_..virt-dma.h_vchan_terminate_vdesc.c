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
struct virt_dma_desc {TYPE_1__ tx; } ;
struct virt_dma_chan {struct virt_dma_desc* cyclic; struct virt_dma_desc* vd_terminated; } ;

/* Variables and functions */
 struct virt_dma_chan* to_virt_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_vdesc_fini (struct virt_dma_desc*) ; 

__attribute__((used)) static inline void vchan_terminate_vdesc(struct virt_dma_desc *vd)
{
	struct virt_dma_chan *vc = to_virt_chan(vd->tx.chan);

	/* free up stuck descriptor */
	if (vc->vd_terminated)
		vchan_vdesc_fini(vc->vd_terminated);

	vc->vd_terminated = vd;
	if (vc->cyclic == vd)
		vc->cyclic = NULL;
}