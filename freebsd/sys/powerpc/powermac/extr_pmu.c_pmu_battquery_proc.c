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
struct pmu_softc {int dummy; } ;
struct pmu_battstate {int dummy; } ;
typedef  int /*<<< orphan*/  cur_batt ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct pmu_battstate*,int) ; 
 int /*<<< orphan*/  curproc ; 
 struct pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  kproc_suspend_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu ; 
 int /*<<< orphan*/  pmu_battery_notify (struct pmu_battstate*,struct pmu_battstate*) ; 
 int pmu_query_battery (struct pmu_softc*,int /*<<< orphan*/ ,struct pmu_battstate*) ; 

__attribute__((used)) static void
pmu_battquery_proc()
{
	struct pmu_softc *sc;
	struct pmu_battstate batt;
	struct pmu_battstate cur_batt;
	int error;

	sc = device_get_softc(pmu);

	bzero(&cur_batt, sizeof(cur_batt));
	while (1) {
		kproc_suspend_check(curproc);
		error = pmu_query_battery(sc, 0, &batt);
		pmu_battery_notify(&batt, &cur_batt);
		cur_batt = batt;
		pause("pmu_batt", hz);
	}
}