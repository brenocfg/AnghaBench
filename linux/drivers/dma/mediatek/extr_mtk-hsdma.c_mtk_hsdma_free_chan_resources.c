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
struct mtk_hsdma_device {int /*<<< orphan*/  pc; int /*<<< orphan*/  pc_refcnt; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_hsdma_free_pchan (struct mtk_hsdma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hsdma_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 struct mtk_hsdma_device* to_hsdma_dev (struct dma_chan*) ; 

__attribute__((used)) static void mtk_hsdma_free_chan_resources(struct dma_chan *c)
{
	struct mtk_hsdma_device *hsdma = to_hsdma_dev(c);

	/* Free all descriptors in all lists on the VC */
	mtk_hsdma_terminate_all(c);

	/* The resource for PC is not freed until all the VCs are destroyed */
	if (!refcount_dec_and_test(&hsdma->pc_refcnt))
		return;

	mtk_hsdma_free_pchan(hsdma, hsdma->pc);
}