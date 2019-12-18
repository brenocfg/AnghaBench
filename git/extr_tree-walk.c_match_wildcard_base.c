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
struct pathspec_item {char* match; int nowildcard_len; } ;

/* Variables and functions */
 scalar_t__ basecmp (struct pathspec_item const*,char const*,char const*,int) ; 
 int entry_interesting ; 

__attribute__((used)) static int match_wildcard_base(const struct pathspec_item *item,
			       const char *base, int baselen,
			       int *matched)
{
	const char *match = item->match;
	/* the wildcard part is not considered in this function */
	int matchlen = item->nowildcard_len;

	if (baselen) {
		int dirlen;
		/*
		 * Return early if base is longer than the
		 * non-wildcard part but it does not match.
		 */
		if (baselen >= matchlen) {
			*matched = matchlen;
			return !basecmp(item, base, match, matchlen);
		}

		dirlen = matchlen;
		while (dirlen && match[dirlen - 1] != '/')
			dirlen--;

		/*
		 * Return early if base is shorter than the
		 * non-wildcard part but it does not match. Note that
		 * base ends with '/' so we are sure it really matches
		 * directory
		 */
		if (basecmp(item, base, match, baselen))
			return 0;
		*matched = baselen;
	} else
		*matched = 0;
	/*
	 * we could have checked entry against the non-wildcard part
	 * that is not in base and does similar never_interesting
	 * optimization as in match_entry. For now just be happy with
	 * base comparison.
	 */
	return entry_interesting;
}