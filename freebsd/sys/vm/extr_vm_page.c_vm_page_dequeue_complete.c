#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGA_QUEUE_STATE_MASK ; 
 int /*<<< orphan*/  PQ_NONE ; 
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_page_dequeue_complete(vm_page_t m)
{

	m->queue = PQ_NONE;
	atomic_thread_fence_rel();
	vm_page_aflag_clear(m, PGA_QUEUE_STATE_MASK);
}