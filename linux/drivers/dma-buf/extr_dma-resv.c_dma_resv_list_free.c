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
struct dma_resv_list {unsigned int shared_count; int /*<<< orphan*/ * shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct dma_resv_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dma_resv_list_free(struct dma_resv_list *list)
{
	unsigned int i;

	if (!list)
		return;

	for (i = 0; i < list->shared_count; ++i)
		dma_fence_put(rcu_dereference_protected(list->shared[i], true));

	kfree_rcu(list, rcu);
}