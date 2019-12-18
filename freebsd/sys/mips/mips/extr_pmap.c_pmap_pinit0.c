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
struct TYPE_7__ {int /*<<< orphan*/  pm_stats; int /*<<< orphan*/  pm_pvchunk; TYPE_1__* pm_asid; int /*<<< orphan*/  pm_active; int /*<<< orphan*/  pm_segtab; } ;
struct TYPE_6__ {scalar_t__ gen; int /*<<< orphan*/  asid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int MAXCPU ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_ASID_RESERVED ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (TYPE_2__*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  curpmap ; 
 int /*<<< orphan*/  kernel_segmap ; 

void
pmap_pinit0(pmap_t pmap)
{
	int i;

	PMAP_LOCK_INIT(pmap);
	pmap->pm_segtab = kernel_segmap;
	CPU_ZERO(&pmap->pm_active);
	for (i = 0; i < MAXCPU; i++) {
		pmap->pm_asid[i].asid = PMAP_ASID_RESERVED;
		pmap->pm_asid[i].gen = 0;
	}
	PCPU_SET(curpmap, pmap);
	TAILQ_INIT(&pmap->pm_pvchunk);
	bzero(&pmap->pm_stats, sizeof pmap->pm_stats);
}