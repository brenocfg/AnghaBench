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
struct pathspec {int nr; int magic; int max_depth; TYPE_1__* items; scalar_t__ recursive; } ;
struct index_state {int dummy; } ;
struct TYPE_2__ {int magic; int len; } ;

/* Variables and functions */
 unsigned int DO_MATCH_EXCLUDE ; 
 int /*<<< orphan*/  GUARD_PATHSPEC (struct pathspec const*,int) ; 
 int MATCHED_EXACTLY ; 
 int MATCHED_FNMATCH ; 
 int MATCHED_RECURSIVELY ; 
 int PATHSPEC_ATTR ; 
 int PATHSPEC_EXCLUDE ; 
 int PATHSPEC_FROMTOP ; 
 int PATHSPEC_GLOB ; 
 int PATHSPEC_ICASE ; 
 int PATHSPEC_LITERAL ; 
 int PATHSPEC_MAXDEPTH ; 
 int match_pathspec_item (struct index_state const*,TYPE_1__*,int,char const*,int,unsigned int) ; 
 scalar_t__ within_depth (char const*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_match_pathspec(const struct index_state *istate,
			     const struct pathspec *ps,
			     const char *name, int namelen,
			     int prefix, char *seen,
			     unsigned flags)
{
	int i, retval = 0, exclude = flags & DO_MATCH_EXCLUDE;

	GUARD_PATHSPEC(ps,
		       PATHSPEC_FROMTOP |
		       PATHSPEC_MAXDEPTH |
		       PATHSPEC_LITERAL |
		       PATHSPEC_GLOB |
		       PATHSPEC_ICASE |
		       PATHSPEC_EXCLUDE |
		       PATHSPEC_ATTR);

	if (!ps->nr) {
		if (!ps->recursive ||
		    !(ps->magic & PATHSPEC_MAXDEPTH) ||
		    ps->max_depth == -1)
			return MATCHED_RECURSIVELY;

		if (within_depth(name, namelen, 0, ps->max_depth))
			return MATCHED_EXACTLY;
		else
			return 0;
	}

	name += prefix;
	namelen -= prefix;

	for (i = ps->nr - 1; i >= 0; i--) {
		int how;

		if ((!exclude &&   ps->items[i].magic & PATHSPEC_EXCLUDE) ||
		    ( exclude && !(ps->items[i].magic & PATHSPEC_EXCLUDE)))
			continue;

		if (seen && seen[i] == MATCHED_EXACTLY)
			continue;
		/*
		 * Make exclude patterns optional and never report
		 * "pathspec ':(exclude)foo' matches no files"
		 */
		if (seen && ps->items[i].magic & PATHSPEC_EXCLUDE)
			seen[i] = MATCHED_FNMATCH;
		how = match_pathspec_item(istate, ps->items+i, prefix, name,
					  namelen, flags);
		if (ps->recursive &&
		    (ps->magic & PATHSPEC_MAXDEPTH) &&
		    ps->max_depth != -1 &&
		    how && how != MATCHED_FNMATCH) {
			int len = ps->items[i].len;
			if (name[len] == '/')
				len++;
			if (within_depth(name+len, namelen-len, 0, ps->max_depth))
				how = MATCHED_EXACTLY;
			else
				how = 0;
		}
		if (how) {
			if (retval < how)
				retval = how;
			if (seen && seen[i] < how)
				seen[i] = how;
		}
	}
	return retval;
}