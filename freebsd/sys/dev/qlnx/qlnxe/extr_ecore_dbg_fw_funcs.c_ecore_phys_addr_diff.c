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
typedef  scalar_t__ u32 ;
struct dbg_bus_mem_addr {scalar_t__ hi; scalar_t__ lo; } ;

/* Variables and functions */

__attribute__((used)) static u32 ecore_phys_addr_diff(struct dbg_bus_mem_addr *a,
								struct dbg_bus_mem_addr *b)
{
	return a->hi == b->hi ? a->lo - b->lo : b->lo - a->lo;
}