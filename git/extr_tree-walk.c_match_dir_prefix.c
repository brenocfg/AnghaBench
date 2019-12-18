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
struct pathspec_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ basecmp (struct pathspec_item const*,char const*,char const*,int) ; 

__attribute__((used)) static int match_dir_prefix(const struct pathspec_item *item,
			    const char *base,
			    const char *match, int matchlen)
{
	if (basecmp(item, base, match, matchlen))
		return 0;

	/*
	 * If the base is a subdirectory of a path which
	 * was specified, all of them are interesting.
	 */
	if (!matchlen ||
	    base[matchlen] == '/' ||
	    match[matchlen - 1] == '/')
		return 1;

	/* Just a random prefix match */
	return 0;
}