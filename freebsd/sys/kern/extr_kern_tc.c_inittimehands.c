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
struct timehands {struct timehands* th_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int nitems (struct timehands*) ; 
 struct timehands* ths ; 
 int timehands_count ; 

__attribute__((used)) static void
inittimehands(void *dummy)
{
	struct timehands *thp;
	int i;

	TUNABLE_INT_FETCH("kern.timecounter.timehands_count",
	    &timehands_count);
	if (timehands_count < 1)
		timehands_count = 1;
	if (timehands_count > nitems(ths))
		timehands_count = nitems(ths);
	for (i = 1, thp = &ths[0]; i < timehands_count;  thp = &ths[i++])
		thp->th_next = &ths[i];
	thp->th_next = &ths[0];
}