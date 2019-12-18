#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_8__ {int aflags; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int PGA_REQUEUE_HEAD ; 
 int /*<<< orphan*/  PQ_INACTIVE ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_inactive (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_pqbatch_submit (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_vm_page_deactivate_noreuse(vm_page_t m)
{

	vm_page_assert_locked(m);

	if (!vm_page_inactive(m)) {
		vm_page_dequeue(m);
		m->queue = PQ_INACTIVE;
	}
	if ((m->aflags & PGA_REQUEUE_HEAD) == 0)
		vm_page_aflag_set(m, PGA_REQUEUE_HEAD);
	vm_page_pqbatch_submit(m, PQ_INACTIVE);
}