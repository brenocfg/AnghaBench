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
struct pathspec_item {int magic; } ;
struct name_entry {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
typedef  enum interesting { ____Placeholder_interesting } interesting ;

/* Variables and functions */
 int PATHSPEC_ICASE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int entry_not_interesting ; 
 int ps_strncmp (struct pathspec_item const*,char const*,int /*<<< orphan*/ ,int) ; 
 int strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int match_entry(const struct pathspec_item *item,
		       const struct name_entry *entry, int pathlen,
		       const char *match, int matchlen,
		       enum interesting *never_interesting)
{
	int m = -1; /* signals that we haven't called strncmp() */

	if (item->magic & PATHSPEC_ICASE)
		/*
		 * "Never interesting" trick requires exact
		 * matching. We could do something clever with inexact
		 * matching, but it's trickier (and not to forget that
		 * strcasecmp is locale-dependent, at least in
		 * glibc). Just disable it for now. It can't be worse
		 * than the wildcard's codepath of '[Tt][Hi][Is][Ss]'
		 * pattern.
		 */
		*never_interesting = entry_not_interesting;
	else if (*never_interesting != entry_not_interesting) {
		/*
		 * We have not seen any match that sorts later
		 * than the current path.
		 */

		/*
		 * Does match sort strictly earlier than path
		 * with their common parts?
		 */
		m = strncmp(match, entry->path,
			    (matchlen < pathlen) ? matchlen : pathlen);
		if (m < 0)
			return 0;

		/*
		 * If we come here even once, that means there is at
		 * least one pathspec that would sort equal to or
		 * later than the path we are currently looking at.
		 * In other words, if we have never reached this point
		 * after iterating all pathspecs, it means all
		 * pathspecs are either outside of base, or inside the
		 * base but sorts strictly earlier than the current
		 * one.  In either case, they will never match the
		 * subsequent entries.  In such a case, we initialized
		 * the variable to -1 and that is what will be
		 * returned, allowing the caller to terminate early.
		 */
		*never_interesting = entry_not_interesting;
	}

	if (pathlen > matchlen)
		return 0;

	if (matchlen > pathlen) {
		if (match[pathlen] != '/')
			return 0;
		if (!S_ISDIR(entry->mode) && !S_ISGITLINK(entry->mode))
			return 0;
	}

	if (m == -1)
		/*
		 * we cheated and did not do strncmp(), so we do
		 * that here.
		 */
		m = ps_strncmp(item, match, entry->path, pathlen);

	/*
	 * If common part matched earlier then it is a hit,
	 * because we rejected the case where path is not a
	 * leading directory and is shorter than match.
	 */
	if (!m)
		/*
		 * match_entry does not check if the prefix part is
		 * matched case-sensitively. If the entry is a
		 * directory and part of prefix, it'll be rematched
		 * eventually by basecmp with special treatment for
		 * the prefix.
		 */
		return 1;

	return 0;
}