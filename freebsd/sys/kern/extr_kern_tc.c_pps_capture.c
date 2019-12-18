#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timehands {scalar_t__ th_generation; TYPE_1__* th_counter; } ;
struct pps_state {scalar_t__ capgen; int /*<<< orphan*/  capcount; int /*<<< orphan*/  capffth; struct timehands* capth; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tc_get_timecount ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ atomic_load_acq_int (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  fftimehands ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct timehands* timehands ; 

void
pps_capture(struct pps_state *pps)
{
	struct timehands *th;

	KASSERT(pps != NULL, ("NULL pps pointer in pps_capture"));
	th = timehands;
	pps->capgen = atomic_load_acq_int(&th->th_generation);
	pps->capth = th;
#ifdef FFCLOCK
	pps->capffth = fftimehands;
#endif
	pps->capcount = th->th_counter->tc_get_timecount(th->th_counter);
	atomic_thread_fence_acq();
	if (pps->capgen != th->th_generation)
		pps->capgen = 0;
}