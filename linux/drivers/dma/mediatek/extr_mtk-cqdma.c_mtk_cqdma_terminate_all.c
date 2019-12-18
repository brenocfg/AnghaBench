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
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_cqdma_free_active_desc (struct dma_chan*) ; 
 int /*<<< orphan*/  mtk_cqdma_free_inactive_desc (struct dma_chan*) ; 

__attribute__((used)) static int mtk_cqdma_terminate_all(struct dma_chan *c)
{
	/* free descriptors not processed yet by hardware */
	mtk_cqdma_free_inactive_desc(c);

	/* free descriptors being processed by hardware */
	mtk_cqdma_free_active_desc(c);

	return 0;
}