#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_5__ {int /*<<< orphan*/  __bits; } ;
typedef  TYPE_1__ cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CLR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CPU_EMPTY (TYPE_1__*) ; 
 int /*<<< orphan*/  PCPU_GET (int /*<<< orphan*/ ) ; 
 TYPE_1__ all_harts ; 
 int /*<<< orphan*/  fence () ; 
 int /*<<< orphan*/  hart ; 
 int /*<<< orphan*/  sbi_remote_fence_i (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 scalar_t__ smp_started ; 

void
pmap_sync_icache(pmap_t pmap, vm_offset_t va, vm_size_t sz)
{
	cpuset_t mask;

	/*
	 * From the RISC-V User-Level ISA V2.2:
	 *
	 * "To make a store to instruction memory visible to all
	 * RISC-V harts, the writing hart has to execute a data FENCE
	 * before requesting that all remote RISC-V harts execute a
	 * FENCE.I."
	 */
	sched_pin();
	mask = all_harts;
	CPU_CLR(PCPU_GET(hart), &mask);
	fence();
	if (!CPU_EMPTY(&mask) && smp_started)
		sbi_remote_fence_i(mask.__bits);
	sched_unpin();
}