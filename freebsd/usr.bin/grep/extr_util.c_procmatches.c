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
struct parsec {int dummy; } ;
struct mprintc {scalar_t__ doctx; } ;

/* Variables and functions */
 scalar_t__ mcount ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  procmatch_match (struct mprintc*,struct parsec*) ; 
 int /*<<< orphan*/  procmatch_nomatch (struct mprintc*,struct parsec*) ; 

__attribute__((used)) static bool
procmatches(struct mprintc *mc, struct parsec *pc, bool matched)
{

	/*
	 * XXX TODO: This should loop over pc->matches and handle things on a
	 * line-by-line basis, setting up a `struct str` as needed.
	 */
	/* Deal with any -B context or context separators */
	if (matched) {
		procmatch_match(mc, pc);

		/* Count the matches if we have a match limit */
		if (mflag) {
			/* XXX TODO: Decrement by number of matched lines */
			mcount -= 1;
			if (mcount <= 0)
				return (false);
		}
	} else if (mc->doctx)
		procmatch_nomatch(mc, pc);

	return (true);
}