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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  PGA_DEQUEUE ; 
 int /*<<< orphan*/  PQ_NONE ; 
 int /*<<< orphan*/  vm_page_assert_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_pqbatch_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_pqstate_cmpset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_queue (int /*<<< orphan*/ ) ; 

void
vm_page_dequeue_deferred(vm_page_t m)
{
	uint8_t queue;

	vm_page_assert_locked(m);

	if ((queue = vm_page_queue(m)) == PQ_NONE)
		return;

	/*
	 * Set PGA_DEQUEUE if it is not already set to handle a concurrent call
	 * to vm_page_dequeue_deferred_free().  In particular, avoid modifying
	 * the page's queue state once vm_page_dequeue_deferred_free() has been
	 * called.  In the event of a race, two batch queue entries for the page
	 * will be created, but the second will have no effect.
	 */
	if (vm_page_pqstate_cmpset(m, queue, queue, PGA_DEQUEUE, PGA_DEQUEUE))
		vm_page_pqbatch_submit(m, queue);
}