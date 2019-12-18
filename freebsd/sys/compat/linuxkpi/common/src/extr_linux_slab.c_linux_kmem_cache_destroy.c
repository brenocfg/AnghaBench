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
struct linux_kmem_cache {int cache_flags; int /*<<< orphan*/  cache_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_KMALLOC ; 
 int SLAB_TYPESAFE_BY_RCU ; 
 int /*<<< orphan*/  free (struct linux_kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void
linux_kmem_cache_destroy(struct linux_kmem_cache *c)
{
	if (unlikely(c->cache_flags & SLAB_TYPESAFE_BY_RCU)) {
		/* make sure all free callbacks have been called */
		rcu_barrier();
	}

	uma_zdestroy(c->cache_zone);
	free(c, M_KMALLOC);
}