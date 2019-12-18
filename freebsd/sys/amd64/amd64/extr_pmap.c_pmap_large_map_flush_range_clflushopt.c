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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  clflushopt (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_clflush_line_size ; 

__attribute__((used)) static void
pmap_large_map_flush_range_clflushopt(vm_offset_t va, vm_size_t len)
{

	for (; len > 0; len -= cpu_clflush_line_size,
	    va += cpu_clflush_line_size)
		clflushopt(va);
}