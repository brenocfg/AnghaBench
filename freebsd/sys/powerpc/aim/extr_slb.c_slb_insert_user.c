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
struct slb {int dummy; } ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {int pm_slb_len; struct slb** pm_slb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mftb () ; 
 int n_slbs ; 

void
slb_insert_user(pmap_t pm, struct slb *slb)
{
	int i;

	PMAP_LOCK_ASSERT(pm, MA_OWNED);

	if (pm->pm_slb_len < n_slbs) {
		i = pm->pm_slb_len;
		pm->pm_slb_len++;
	} else {
		i = mftb() % n_slbs;
	}

	/* Note that this replacement is atomic with respect to trap_subr */
	pm->pm_slb[i] = slb;
}