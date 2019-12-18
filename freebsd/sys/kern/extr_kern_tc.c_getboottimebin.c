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
struct timehands {scalar_t__ th_generation; struct bintime th_boottime; } ;

/* Variables and functions */
 scalar_t__ atomic_load_acq_int (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_thread_fence_acq () ; 
 struct timehands* timehands ; 

void
getboottimebin(struct bintime *boottimebin)
{
	struct timehands *th;
	u_int gen;

	do {
		th = timehands;
		gen = atomic_load_acq_int(&th->th_generation);
		*boottimebin = th->th_boottime;
		atomic_thread_fence_acq();
	} while (gen == 0 || gen != th->th_generation);
}