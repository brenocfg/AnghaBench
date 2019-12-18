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
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_5__ {int /*<<< orphan*/  pm_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_LOCK_INIT (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  moea_pinit (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
moea_pinit0(mmu_t mmu, pmap_t pm)
{

	PMAP_LOCK_INIT(pm);
	moea_pinit(mmu, pm);
	bzero(&pm->pm_stats, sizeof(pm->pm_stats));
}