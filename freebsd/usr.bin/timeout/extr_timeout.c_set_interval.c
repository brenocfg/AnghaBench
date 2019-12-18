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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  tim ;
typedef  scalar_t__ suseconds_t ;
struct TYPE_2__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct itimerval {TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct itimerval*,int /*<<< orphan*/ ,int) ; 
 int setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_interval(double iv)
{
	struct itimerval tim;

	memset(&tim, 0, sizeof(tim));
	tim.it_value.tv_sec = (time_t)iv;
	iv -= (time_t)iv;
	tim.it_value.tv_usec = (suseconds_t)(iv * 1000000UL);

	if (setitimer(ITIMER_REAL, &tim, NULL) == -1)
		err(EX_OSERR, "setitimer()");
}