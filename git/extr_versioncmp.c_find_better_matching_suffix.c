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
struct suffix_match {int len; int start; int conf_pos; } ;

/* Variables and functions */
 scalar_t__ starts_with (char const*,char const*) ; 

__attribute__((used)) static void find_better_matching_suffix(const char *tagname, const char *suffix,
					int suffix_len, int start, int conf_pos,
					struct suffix_match *match)
{
	/*
	 * A better match either starts earlier or starts at the same offset
	 * but is longer.
	 */
	int end = match->len < suffix_len ? match->start : match->start-1;
	int i;
	for (i = start; i <= end; i++)
		if (starts_with(tagname + i, suffix)) {
			match->conf_pos = conf_pos;
			match->start = i;
			match->len = suffix_len;
			break;
		}
}