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
struct TYPE_5__ {int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_LAUNDRY ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  vm_page_mvqueue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_wired (TYPE_1__*) ; 

void
vm_page_launder(vm_page_t m)
{

	if ((m->oflags & VPO_UNMANAGED) != 0 || vm_page_wired(m))
		return;
	vm_page_mvqueue(m, PQ_LAUNDRY);
}