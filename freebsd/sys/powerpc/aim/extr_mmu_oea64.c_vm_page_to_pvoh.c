#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct pvo_head {int dummy; } ;
struct TYPE_5__ {struct pvo_head mdpg_pvoh; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PV_LOCKPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pvo_head *
vm_page_to_pvoh(vm_page_t m)
{

	mtx_assert(PV_LOCKPTR(VM_PAGE_TO_PHYS(m)), MA_OWNED);
	return (&m->md.mdpg_pvoh);
}