#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_5__ {TYPE_1__* task; } ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ VM_MAX_ADDRESS ; 
 scalar_t__ VM_MIN_ADDRESS ; 
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  kernel_map ; 

vm_map_t
db_map_addr(vm_offset_t addr)
{
#if 0
	thread_t	thread;

	/*
	 *	We want to return kernel_map for all
	 *	non-user addresses, even when debugging
	 *	kernel tasks with their own maps.
	 */

	if ((VM_MIN_ADDRESS <= addr) &&
	    (addr < VM_MAX_ADDRESS) &&
	    ((thread = current_thread()) != NULL))
	    return thread->task->map;
	else
#endif
	    return kernel_map;
}