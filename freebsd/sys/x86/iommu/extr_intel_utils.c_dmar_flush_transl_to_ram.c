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
struct dmar_unit {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMAR_IS_COHERENT (struct dmar_unit*) ; 
 int /*<<< orphan*/  pmap_force_invalidate_cache_range (uintptr_t,uintptr_t) ; 

__attribute__((used)) static void
dmar_flush_transl_to_ram(struct dmar_unit *unit, void *dst, size_t sz)
{

	if (DMAR_IS_COHERENT(unit))
		return;
	/*
	 * If DMAR does not snoop paging structures accesses, flush
	 * CPU cache to memory.
	 */
	pmap_force_invalidate_cache_range((uintptr_t)dst, (uintptr_t)dst + sz);
}