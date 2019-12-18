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
typedef  scalar_t__ u_int ;
struct bintime {int dummy; } ;
struct timehands {scalar_t__ th_generation; int th_scale; struct bintime th_offset; } ;

/* Variables and functions */
 scalar_t__ atomic_load_acq_int (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 int /*<<< orphan*/  bintime_addx (struct bintime*,int) ; 
 int tc_delta (struct timehands*) ; 
 struct timehands* timehands ; 

void
binuptime(struct bintime *bt)
{
	struct timehands *th;
	u_int gen;

	do {
		th = timehands;
		gen = atomic_load_acq_int(&th->th_generation);
		*bt = th->th_offset;
		bintime_addx(bt, th->th_scale * tc_delta(th));
		atomic_thread_fence_acq();
	} while (gen == 0 || gen != th->th_generation);
}