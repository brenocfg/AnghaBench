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

/* Variables and functions */
 scalar_t__ atomic_fetchadd_long (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uma_kmem_limit ; 
 int /*<<< orphan*/  uma_kmem_total ; 
 int /*<<< orphan*/  uma_reclaim_wakeup () ; 

__attribute__((used)) static inline void
uma_total_inc(unsigned long size)
{

	if (atomic_fetchadd_long(&uma_kmem_total, size) > uma_kmem_limit)
		uma_reclaim_wakeup();
}