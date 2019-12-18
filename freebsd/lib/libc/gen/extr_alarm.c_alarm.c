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
struct TYPE_2__ {unsigned int tv_sec; scalar_t__ tv_usec; } ;
struct itimerval {TYPE_1__ it_value; int /*<<< orphan*/  it_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 scalar_t__ setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 
 int /*<<< orphan*/  timerclear (int /*<<< orphan*/ *) ; 

unsigned int
alarm(unsigned int secs)
{
	struct itimerval it, oitv;
	struct itimerval *itp = &it;

	timerclear(&itp->it_interval);
	itp->it_value.tv_sec = secs;
	itp->it_value.tv_usec = 0;
	if (setitimer(ITIMER_REAL, itp, &oitv) < 0)
		return (-1);
	if (oitv.it_value.tv_usec)
		oitv.it_value.tv_sec++;
	return (oitv.it_value.tv_sec);
}