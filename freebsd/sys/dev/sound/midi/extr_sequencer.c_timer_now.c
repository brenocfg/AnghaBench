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
struct timeval {unsigned long long tv_sec; scalar_t__ tv_usec; } ;
struct seq_softc {scalar_t__ timerrun; unsigned long long timerbase; int /*<<< orphan*/  timersub; struct timeval timerstop; } ;

/* Variables and functions */
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
timer_now(struct seq_softc *t)
{
	struct timeval now;
	unsigned long long i;
	int ret;

	if (t->timerrun == 0)
		now = t->timerstop;
	else
		getmicrotime(&now);

	timevalsub(&now, &t->timersub);

	i = now.tv_sec * 1000000ull;
	i += now.tv_usec;
	i *= t->timerbase;
/*	i /= t->tempo; */
	i /= 1000000ull;

	ret = i;
	/*
	 * printf("timer_now: %llu %d\n", i, ret);
	 */

	return ret;
}