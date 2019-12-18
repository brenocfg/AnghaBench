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
struct linux_kmem_rcu {int /*<<< orphan*/  rcu_head; } ;
struct linux_kmem_cache {int dummy; } ;

/* Variables and functions */
 struct linux_kmem_rcu* LINUX_KMEM_TO_RCU (struct linux_kmem_cache*,void*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_kmem_cache_free_rcu_callback ; 

void
linux_kmem_cache_free_rcu(struct linux_kmem_cache *c, void *m)
{
	struct linux_kmem_rcu *rcu = LINUX_KMEM_TO_RCU(c, m);

	call_rcu(&rcu->rcu_head, linux_kmem_cache_free_rcu_callback);
}