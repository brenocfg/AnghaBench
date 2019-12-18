#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dmar_unit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_BARRIER_USEQ ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_barrier_enter (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_barrier_exit (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_match_quirks (struct dmar_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_use_nb ; 

void
dmar_quirks_pre_use(struct dmar_unit *dmar)
{

	if (!dmar_barrier_enter(dmar, DMAR_BARRIER_USEQ))
		return;
	DMAR_LOCK(dmar);
	dmar_match_quirks(dmar, pre_use_nb, nitems(pre_use_nb),
	    NULL, 0);
	dmar_barrier_exit(dmar, DMAR_BARRIER_USEQ);
}