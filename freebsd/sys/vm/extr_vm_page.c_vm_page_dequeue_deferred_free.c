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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ ref_count; int aflags; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PGA_DEQUEUE ; 
 int /*<<< orphan*/  PQ_NONE ; 
 int /*<<< orphan*/  atomic_load_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  vm_page_pqbatch_submit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_pqstate_cmpset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
vm_page_dequeue_deferred_free(vm_page_t m)
{
	uint8_t queue;

	KASSERT(m->ref_count == 0, ("page %p has references", m));

	for (;;) {
		if ((m->aflags & PGA_DEQUEUE) != 0)
			return;
		atomic_thread_fence_acq();
		if ((queue = atomic_load_8(&m->queue)) == PQ_NONE)
			return;
		if (vm_page_pqstate_cmpset(m, queue, queue, PGA_DEQUEUE,
		    PGA_DEQUEUE)) {
			vm_page_pqbatch_submit(m, queue);
			break;
		}
	}
}