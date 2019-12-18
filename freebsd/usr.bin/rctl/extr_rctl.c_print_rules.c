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
 char* humanize_amount (char*) ; 
 char* humanize_ids (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
print_rules(char *rules, int hflag, int nflag)
{
	char *rule;

	while ((rule = strsep(&rules, ",")) != NULL) {
		if (rule[0] == '\0')
			break; /* XXX */
		if (nflag == 0)
			rule = humanize_ids(rule);
		if (hflag)
			rule = humanize_amount(rule);
		printf("%s\n", rule);
	}
}