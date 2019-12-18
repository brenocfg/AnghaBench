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
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  cpu_l2cache_drain_writebuf () ; 
 int /*<<< orphan*/  dsb () ; 

void
generic_bs_barrier(bus_space_tag_t t, bus_space_handle_t bsh, bus_size_t offset,
    bus_size_t len, int flags)
{

	/*
	 * dsb() will drain the L1 write buffer and establish a memory access
	 * barrier point on platforms where that has meaning.  On a write we
	 * also need to drain the L2 write buffer, because most on-chip memory
	 * mapped devices are downstream of the L2 cache.  Note that this needs
	 * to be done even for memory mapped as Device type, because while
	 * Device memory is not cached, writes to it are still buffered.
	 */
	dsb();
	if (flags & BUS_SPACE_BARRIER_WRITE) {
		cpu_l2cache_drain_writebuf();
	}
}