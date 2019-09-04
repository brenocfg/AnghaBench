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
 int NUM_REV_PARSE_RULES ; 
 int /*<<< orphan*/  mkpath (char const*,int const,char const*) ; 
 char const** ref_rev_parse_rules ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int refname_match(const char *abbrev_name, const char *full_name)
{
	const char **p;
	const int abbrev_name_len = strlen(abbrev_name);
	const int num_rules = NUM_REV_PARSE_RULES;

	for (p = ref_rev_parse_rules; *p; p++)
		if (!strcmp(full_name, mkpath(*p, abbrev_name_len, abbrev_name)))
			return &ref_rev_parse_rules[num_rules] - p;

	return 0;
}