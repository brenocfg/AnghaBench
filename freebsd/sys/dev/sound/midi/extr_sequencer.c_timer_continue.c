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
struct timeval {int dummy; } ;
struct seq_softc {int timerrun; int /*<<< orphan*/  timersub; int /*<<< orphan*/  timerstop; } ;

/* Variables and functions */
 int /*<<< orphan*/  getmicrotime (struct timeval*) ; 
 int /*<<< orphan*/  timevaladd (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
timer_continue(struct seq_softc *t)
{
	struct timeval now;

	if (t->timerrun == 1)
		return;
	t->timerrun = 1;
	getmicrotime(&now);
	timevalsub(&now, &t->timerstop);
	timevaladd(&t->timersub, &now);
}