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
 int /*<<< orphan*/  __vmcache_dckill () ; 
 int /*<<< orphan*/  __vmcache_ickill () ; 
 int /*<<< orphan*/  __vmcache_l2kill () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 

void flush_cache_all_hexagon(void)
{
	unsigned long flags;
	local_irq_save(flags);
	__vmcache_ickill();
	__vmcache_dckill();
	__vmcache_l2kill();
	local_irq_restore(flags);
	mb();
}