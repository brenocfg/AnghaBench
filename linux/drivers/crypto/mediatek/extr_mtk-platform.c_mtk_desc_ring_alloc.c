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
struct mtk_ring {int /*<<< orphan*/  cmd_dma; void* cmd_base; int /*<<< orphan*/  res_dma; void* res_base; void* res_next; void* cmd_next; } ;
struct mtk_cryp {int /*<<< orphan*/  dev; struct mtk_ring** ring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTK_DESC_RING_SZ ; 
 int MTK_RING_MAX ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtk_ring*) ; 
 struct mtk_ring* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_desc_ring_alloc(struct mtk_cryp *cryp)
{
	struct mtk_ring **ring = cryp->ring;
	int i, err = ENOMEM;

	for (i = 0; i < MTK_RING_MAX; i++) {
		ring[i] = kzalloc(sizeof(**ring), GFP_KERNEL);
		if (!ring[i])
			goto err_cleanup;

		ring[i]->cmd_base = dma_alloc_coherent(cryp->dev,
						       MTK_DESC_RING_SZ,
						       &ring[i]->cmd_dma,
						       GFP_KERNEL);
		if (!ring[i]->cmd_base)
			goto err_cleanup;

		ring[i]->res_base = dma_alloc_coherent(cryp->dev,
						       MTK_DESC_RING_SZ,
						       &ring[i]->res_dma,
						       GFP_KERNEL);
		if (!ring[i]->res_base)
			goto err_cleanup;

		ring[i]->cmd_next = ring[i]->cmd_base;
		ring[i]->res_next = ring[i]->res_base;
	}
	return 0;

err_cleanup:
	for (; i--; ) {
		dma_free_coherent(cryp->dev, MTK_DESC_RING_SZ,
				  ring[i]->res_base, ring[i]->res_dma);
		dma_free_coherent(cryp->dev, MTK_DESC_RING_SZ,
				  ring[i]->cmd_base, ring[i]->cmd_dma);
		kfree(ring[i]);
	}
	return err;
}