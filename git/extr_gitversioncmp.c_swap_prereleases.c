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
struct suffix_match {int member_0; int member_1; int member_2; int conf_pos; } ;
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct TYPE_3__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_better_matching_suffix (char const*,char const*,int,int,int,struct suffix_match*) ; 
 TYPE_2__* prereleases ; 
 int strlen (char const*) ; 

__attribute__((used)) static int swap_prereleases(const char *s1,
			    const char *s2,
			    int off,
			    int *diff)
{
	int i;
	struct suffix_match match1 = { -1, off, -1 };
	struct suffix_match match2 = { -1, off, -1 };

	for (i = 0; i < prereleases->nr; i++) {
		const char *suffix = prereleases->items[i].string;
		int start, suffix_len = strlen(suffix);
		if (suffix_len < off)
			start = off - suffix_len;
		else
			start = 0;
		find_better_matching_suffix(s1, suffix, suffix_len, start,
					    i, &match1);
		find_better_matching_suffix(s2, suffix, suffix_len, start,
					    i, &match2);
	}
	if (match1.conf_pos == -1 && match2.conf_pos == -1)
		return 0;
	if (match1.conf_pos == match2.conf_pos)
		/* Found the same suffix in both, e.g. "-rc" in "v1.0-rcX"
		 * and "v1.0-rcY": the caller should decide based on "X"
		 * and "Y". */
		return 0;

	if (match1.conf_pos >= 0 && match2.conf_pos >= 0)
		*diff = match1.conf_pos - match2.conf_pos;
	else if (match1.conf_pos >= 0)
		*diff = -1;
	else /* if (match2.conf_pos >= 0) */
		*diff = 1;
	return 1;
}