#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_7__ {int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PQ_UNSWAPPABLE ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  vm_page_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_enqueue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_wired (TYPE_1__*) ; 

void
vm_page_unswappable(vm_page_t m)
{

	vm_page_assert_locked(m);
	KASSERT(!vm_page_wired(m) && (m->oflags & VPO_UNMANAGED) == 0,
	    ("page %p already unswappable", m));

	vm_page_dequeue(m);
	vm_page_enqueue(m, PQ_UNSWAPPABLE);
}