#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int exclude_user; int exclude_kernel; int exclude_hv; } ;
struct perf_event {TYPE_1__ attr; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int PPMU_ARCH_207S ; 
 unsigned int PPMU_LIMITED_PMC_OK ; 
 unsigned int PPMU_LIMITED_PMC_REQD ; 
 TYPE_2__* ppmu ; 

__attribute__((used)) static int check_excludes(struct perf_event **ctrs, unsigned int cflags[],
			  int n_prev, int n_new)
{
	int eu = 0, ek = 0, eh = 0;
	int i, n, first;
	struct perf_event *event;

	/*
	 * If the PMU we're on supports per event exclude settings then we
	 * don't need to do any of this logic. NB. This assumes no PMU has both
	 * per event exclude and limited PMCs.
	 */
	if (ppmu->flags & PPMU_ARCH_207S)
		return 0;

	n = n_prev + n_new;
	if (n <= 1)
		return 0;

	first = 1;
	for (i = 0; i < n; ++i) {
		if (cflags[i] & PPMU_LIMITED_PMC_OK) {
			cflags[i] &= ~PPMU_LIMITED_PMC_REQD;
			continue;
		}
		event = ctrs[i];
		if (first) {
			eu = event->attr.exclude_user;
			ek = event->attr.exclude_kernel;
			eh = event->attr.exclude_hv;
			first = 0;
		} else if (event->attr.exclude_user != eu ||
			   event->attr.exclude_kernel != ek ||
			   event->attr.exclude_hv != eh) {
			return -EAGAIN;
		}
	}

	if (eu || ek || eh)
		for (i = 0; i < n; ++i)
			if (cflags[i] & PPMU_LIMITED_PMC_OK)
				cflags[i] |= PPMU_LIMITED_PMC_REQD;

	return 0;
}