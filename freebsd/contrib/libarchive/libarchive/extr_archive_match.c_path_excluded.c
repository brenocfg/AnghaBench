#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct match {scalar_t__ matches; struct match* next; } ;
struct TYPE_4__ {struct match* first; int /*<<< orphan*/  unmatched_count; } ;
struct TYPE_3__ {struct match* first; } ;
struct archive_match {TYPE_2__ inclusions; TYPE_1__ exclusions; } ;

/* Variables and functions */
 int match_path_exclusion (struct archive_match*,struct match*,int,void const*) ; 
 int match_path_inclusion (struct archive_match*,struct match*,int,void const*) ; 

__attribute__((used)) static int
path_excluded(struct archive_match *a, int mbs, const void *pathname)
{
	struct match *match;
	struct match *matched;
	int r;

	if (a == NULL)
		return (0);

	/* Mark off any unmatched inclusions. */
	/* In particular, if a filename does appear in the archive and
	 * is explicitly included and excluded, then we don't report
	 * it as missing even though we don't extract it.
	 */
	matched = NULL;
	for (match = a->inclusions.first; match != NULL;
	    match = match->next){
		if (match->matches == 0 &&
		    (r = match_path_inclusion(a, match, mbs, pathname)) != 0) {
			if (r < 0)
				return (r);
			a->inclusions.unmatched_count--;
			match->matches++;
			matched = match;
		}
	}

	/* Exclusions take priority */
	for (match = a->exclusions.first; match != NULL;
	    match = match->next){
		r = match_path_exclusion(a, match, mbs, pathname);
		if (r)
			return (r);
	}

	/* It's not excluded and we found an inclusion above, so it's
	 * included. */
	if (matched != NULL)
		return (0);


	/* We didn't find an unmatched inclusion, check the remaining ones. */
	for (match = a->inclusions.first; match != NULL;
	    match = match->next){
		/* We looked at previously-unmatched inclusions already. */
		if (match->matches > 0 &&
		    (r = match_path_inclusion(a, match, mbs, pathname)) != 0) {
			if (r < 0)
				return (r);
			match->matches++;
			return (0);
		}
	}

	/* If there were inclusions, default is to exclude. */
	if (a->inclusions.first != NULL)
	    return (1);

	/* No explicit inclusions, default is to match. */
	return (0);
}