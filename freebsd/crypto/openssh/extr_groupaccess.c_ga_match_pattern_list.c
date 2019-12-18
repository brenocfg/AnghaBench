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
 int /*<<< orphan*/ * groups_byname ; 
 int match_pattern_list (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int ngroups ; 

int
ga_match_pattern_list(const char *group_pattern)
{
	int i, found = 0;

	for (i = 0; i < ngroups; i++) {
		switch (match_pattern_list(groups_byname[i], group_pattern, 0)) {
		case -1:
			return 0;	/* Negated match wins */
		case 0:
			continue;
		case 1:
			found = 1;
		}
	}
	return found;
}