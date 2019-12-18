#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
struct TYPE_7__ {int /*<<< orphan*/  pm_l1; } ;
struct TYPE_6__ {int pm_satp; int /*<<< orphan*/  pm_active; int /*<<< orphan*/  pm_l1; int /*<<< orphan*/  pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (TYPE_1__*) ; 
 int SATP_MODE_SV39 ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* kernel_pmap ; 
 int /*<<< orphan*/  pmap_activate_boot (TYPE_1__*) ; 
 int vtophys (int /*<<< orphan*/ ) ; 

void
pmap_pinit0(pmap_t pmap)
{

	PMAP_LOCK_INIT(pmap);
	bzero(&pmap->pm_stats, sizeof(pmap->pm_stats));
	pmap->pm_l1 = kernel_pmap->pm_l1;
	pmap->pm_satp = SATP_MODE_SV39 | (vtophys(pmap->pm_l1) >> PAGE_SHIFT);
	CPU_ZERO(&pmap->pm_active);
	pmap_activate_boot(pmap);
}