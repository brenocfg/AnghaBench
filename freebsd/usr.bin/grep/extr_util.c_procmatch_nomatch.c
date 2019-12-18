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
struct parsec {int /*<<< orphan*/  ln; } ;
struct mprintc {scalar_t__ tail; int /*<<< orphan*/  last_outed; } ;

/* Variables and functions */
 scalar_t__ Bflag ; 
 int /*<<< orphan*/  clearqueue () ; 
 scalar_t__ enqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grep_printline (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void
procmatch_nomatch(struct mprintc *mc, struct parsec *pc)
{

	/* Deal with any -A context as needed */
	if (mc->tail > 0) {
		grep_printline(&pc->ln, '-');
		mc->tail--;
		if (Bflag > 0)
			clearqueue();
	} else if (Bflag == 0 || (Bflag > 0 && enqueue(&pc->ln)))
		/*
		 * Enqueue non-matching lines for -B context. If we're not
		 * actually doing -B context or if the enqueue resulted in a
		 * line being rotated out, then go ahead and increment
		 * last_outed to signify a gap between context/match.
		 */
		++mc->last_outed;
}