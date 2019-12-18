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
struct coh901318_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  dmapool; } ;
struct coh901318_lli {int link_addr; struct coh901318_lli* virt_link_addr; void* phy_this; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_POOL_COUNTER_ADD (struct coh901318_pool*,int) ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  coh901318_lli_free (struct coh901318_pool*,struct coh901318_lli**) ; 
 struct coh901318_lli* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct coh901318_lli *
coh901318_lli_alloc(struct coh901318_pool *pool, unsigned int len)
{
	int i;
	struct coh901318_lli *head;
	struct coh901318_lli *lli;
	struct coh901318_lli *lli_prev;
	dma_addr_t phy;

	if (len == 0)
		return NULL;

	spin_lock(&pool->lock);

	head = dma_pool_alloc(pool->dmapool, GFP_NOWAIT, &phy);

	if (head == NULL)
		goto err;

	DEBUGFS_POOL_COUNTER_ADD(pool, 1);

	lli = head;
	lli->phy_this = phy;
	lli->link_addr = 0x00000000;
	lli->virt_link_addr = NULL;

	for (i = 1; i < len; i++) {
		lli_prev = lli;

		lli = dma_pool_alloc(pool->dmapool, GFP_NOWAIT, &phy);

		if (lli == NULL)
			goto err_clean_up;

		DEBUGFS_POOL_COUNTER_ADD(pool, 1);
		lli->phy_this = phy;
		lli->link_addr = 0x00000000;
		lli->virt_link_addr = NULL;

		lli_prev->link_addr = phy;
		lli_prev->virt_link_addr = lli;
	}

	spin_unlock(&pool->lock);

	return head;

 err:
	spin_unlock(&pool->lock);
	return NULL;

 err_clean_up:
	lli_prev->link_addr = 0x00000000U;
	spin_unlock(&pool->lock);
	coh901318_lli_free(pool, &head);
	return NULL;
}