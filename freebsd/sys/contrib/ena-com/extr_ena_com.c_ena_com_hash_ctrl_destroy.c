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
struct ena_rss {int /*<<< orphan*/ * hash_ctrl; int /*<<< orphan*/  hash_ctrl_mem_handle; int /*<<< orphan*/  hash_ctrl_dma_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_rss rss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_MEM_FREE_COHERENT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_com_hash_ctrl_destroy(struct ena_com_dev *ena_dev)
{
	struct ena_rss *rss = &ena_dev->rss;

	if (rss->hash_ctrl)
		ENA_MEM_FREE_COHERENT(ena_dev->dmadev,
				      sizeof(*rss->hash_ctrl),
				      rss->hash_ctrl,
				      rss->hash_ctrl_dma_addr,
				      rss->hash_ctrl_mem_handle);
	rss->hash_ctrl = NULL;
}