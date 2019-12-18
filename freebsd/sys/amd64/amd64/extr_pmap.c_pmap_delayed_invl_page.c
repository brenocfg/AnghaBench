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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ u_long ;
struct TYPE_4__ {scalar_t__ gen; } ;
struct TYPE_5__ {TYPE_1__ md_invl_gen; } ;
struct TYPE_6__ {TYPE_2__ td_md; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  VM_PAGE_TO_PV_LIST_LOCK (int /*<<< orphan*/ ) ; 
 TYPE_3__* curthread ; 
 scalar_t__* pmap_delayed_invl_genp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_delayed_invl_page(vm_page_t m)
{
	u_long gen, *m_gen;

	rw_assert(VM_PAGE_TO_PV_LIST_LOCK(m), RA_WLOCKED);
	gen = curthread->td_md.md_invl_gen.gen;
	if (gen == 0)
		return;
	m_gen = pmap_delayed_invl_genp(m);
	if (*m_gen < gen)
		*m_gen = gen;
}