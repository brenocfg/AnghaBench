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

/* Variables and functions */
 int /*<<< orphan*/  ask (char*,...) ; 
 scalar_t__ batch ; 
 char* buf ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ force ; 
 scalar_t__ noreverse ; 
 int /*<<< orphan*/  pch_swap () ; 
 int reverse ; 
 int /*<<< orphan*/  say (char*,...) ; 
 int skip_rest_of_patch ; 
 scalar_t__ verbose ; 

__attribute__((used)) static bool
handle_creation(bool out_existed, bool *remove)
{
	bool reverse_seen;

	reverse_seen = false;
	if (reverse && out_existed) {
		/*
		 * If the patch creates the file and we're reversing the patch,
		 * then we need to indicate to the patch processor that it's OK
		 * to remove this file.
		 */
		*remove = true;
	} else if (!reverse && out_existed) {
		/*
		 * Otherwise, we need to blow the horn because the patch appears
		 * to be reversed/already applied.  For non-batch jobs, we'll
		 * prompt to figure out what we should be trying to do to raise
		 * awareness of the issue.  batch (-t) processing suppresses the
		 * questions and just assumes that we're reversed if it looks
		 * like we are, which is always the case if we've reached this
		 * branch.
		 */
		if (force) {
			skip_rest_of_patch = true;
			return (false);
		}
		if (noreverse) {
			/* If -N is supplied, however, we bail out/ignore. */
			say("Ignoring previously applied (or reversed) patch.\n");
			skip_rest_of_patch = true;
			return (false);
		}

		/* Unreversed... suspicious if the file existed. */
		if (!pch_swap())
			fatal("lost hunk on alloc error!\n");

		reverse = !reverse;

		if (batch) {
			if (verbose)
				say("Patch creates file that already exists, %s %seversed",
				    reverse ? "Assuming" : "Ignoring",
				    reverse ? "R" : "Unr");
		} else {
			ask("Patch creates file that already exists!  %s -R? [y] ",
			    reverse ? "Assume" : "Ignore");

			if (*buf == 'n') {
				ask("Apply anyway? [n]");
				if (*buf != 'y')
					/* Don't apply; error out. */
					skip_rest_of_patch = true;
				else
					/* Attempt to apply. */
					reverse_seen = true;
				reverse = !reverse;
				if (!pch_swap())
					fatal("lost hunk on alloc error!\n");
			} else {
				/*
				 * They've opted to assume -R; effectively the
				 * same as the first branch in this function,
				 * but the decision is here rather than in a
				 * prior patch/hunk as in that branch.
				 */
				*remove = true;
			}
		}
	}

	/*
	 * The return value indicates if we offered a chance to reverse but the
	 * user declined.  This keeps the main patch processor in the loop since
	 * we've taken this out of the normal flow of hunk processing to
	 * simplify logic a little bit.
	 */
	return (reverse_seen);
}