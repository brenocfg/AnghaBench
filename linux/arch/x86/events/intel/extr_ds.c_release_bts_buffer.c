#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cpu_hw_events {int /*<<< orphan*/ * ds_bts_vaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  bts_buffer; } ;
struct TYPE_6__ {TYPE_1__ cpu_debug_buffers; } ;
struct TYPE_5__ {int /*<<< orphan*/  bts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTS_BUFFER_SIZE ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  ds_clear_cea (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsfree_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* get_cpu_entry_area (int) ; 
 struct cpu_hw_events* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static void release_bts_buffer(int cpu)
{
	struct cpu_hw_events *hwev = per_cpu_ptr(&cpu_hw_events, cpu);
	void *cea;

	if (!x86_pmu.bts)
		return;

	/* Clear the fixmap */
	cea = &get_cpu_entry_area(cpu)->cpu_debug_buffers.bts_buffer;
	ds_clear_cea(cea, BTS_BUFFER_SIZE);
	dsfree_pages(hwev->ds_bts_vaddr, BTS_BUFFER_SIZE);
	hwev->ds_bts_vaddr = NULL;
}