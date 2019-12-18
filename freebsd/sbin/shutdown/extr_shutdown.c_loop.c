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
struct interval {scalar_t__ timeleft; int timetowait; } ;

/* Variables and functions */
 scalar_t__ NOLOG_TIME ; 
 int /*<<< orphan*/  die_you_gravy_sucking_pig_dog () ; 
 int /*<<< orphan*/  nolog () ; 
 scalar_t__ offset ; 
 int /*<<< orphan*/  sleep (scalar_t__) ; 
 int /*<<< orphan*/  timewarn (scalar_t__) ; 
 struct interval* tlist ; 

__attribute__((used)) static void
loop(void)
{
	struct interval *tp;
	u_int sltime;
	int logged;

	if (offset <= NOLOG_TIME) {
		logged = 1;
		nolog();
	}
	else
		logged = 0;
	tp = tlist;
	if (tp->timeleft < offset)
		(void)sleep((u_int)(offset - tp->timeleft));
	else {
		while (tp->timeleft && offset < tp->timeleft)
			++tp;
		/*
		 * Warn now, if going to sleep more than a fifth of
		 * the next wait time.
		 */
		if ((sltime = offset - tp->timeleft)) {
			if (sltime > (u_int)(tp->timetowait / 5))
				timewarn(offset);
			(void)sleep(sltime);
		}
	}
	for (;; ++tp) {
		timewarn(tp->timeleft);
		if (!logged && tp->timeleft <= NOLOG_TIME) {
			logged = 1;
			nolog();
		}
		(void)sleep((u_int)tp->timetowait);
		if (!tp->timeleft)
			break;
	}
	die_you_gravy_sucking_pig_dog();
}