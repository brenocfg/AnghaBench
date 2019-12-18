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
struct virt_dma_desc {int /*<<< orphan*/  node; } ;
struct uniphier_mdmac_desc {int dummy; } ;
struct uniphier_mdmac_chan {struct uniphier_mdmac_desc* md; int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct uniphier_mdmac_desc* to_uniphier_mdmac_desc (struct virt_dma_desc*) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct uniphier_mdmac_desc *
uniphier_mdmac_next_desc(struct uniphier_mdmac_chan *mc)
{
	struct virt_dma_desc *vd;

	vd = vchan_next_desc(&mc->vc);
	if (!vd) {
		mc->md = NULL;
		return NULL;
	}

	list_del(&vd->node);

	mc->md = to_uniphier_mdmac_desc(vd);

	return mc->md;
}