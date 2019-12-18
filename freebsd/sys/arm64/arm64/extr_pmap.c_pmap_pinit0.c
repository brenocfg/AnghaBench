#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_6__ {scalar_t__ rt_root; } ;
struct TYPE_7__ {int /*<<< orphan*/  pm_cookie; TYPE_1__ pm_root; int /*<<< orphan*/  pm_l0_paddr; int /*<<< orphan*/ * pm_l0; int /*<<< orphan*/  pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASID_RESERVED_FOR_PID_0 ; 
 int /*<<< orphan*/  COOKIE_FROM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (TYPE_2__*) ; 
 int /*<<< orphan*/  READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  curpmap ; 
 int /*<<< orphan*/  ttbr0_el1 ; 

void
pmap_pinit0(pmap_t pmap)
{

	PMAP_LOCK_INIT(pmap);
	bzero(&pmap->pm_stats, sizeof(pmap->pm_stats));
	pmap->pm_l0_paddr = READ_SPECIALREG(ttbr0_el1);
	pmap->pm_l0 = (pd_entry_t *)PHYS_TO_DMAP(pmap->pm_l0_paddr);
	pmap->pm_root.rt_root = 0;
	pmap->pm_cookie = COOKIE_FROM(ASID_RESERVED_FOR_PID_0, INT_MIN);

	PCPU_SET(curpmap, pmap);
}