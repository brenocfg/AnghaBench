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
struct mac_bsdextended_rule {int dummy; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int bsde_add_rule (int*,struct mac_bsdextended_rule*,int,char*) ; 
 int bsde_parse_rule (int,char**,struct mac_bsdextended_rule*,int,char*) ; 
 int bsde_rule_to_string (struct mac_bsdextended_rule*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
add_rule(int argc, char *argv[])
{
	char errstr[BUFSIZ], charstr[BUFSIZ];
	struct mac_bsdextended_rule rule;
	int error, rulenum;

	error = bsde_parse_rule(argc, argv, &rule, BUFSIZ, errstr);
	if (error) {
		warnx("%s", errstr);
		return;
	}

	error = bsde_add_rule(&rulenum, &rule, BUFSIZ, errstr);
	if (error) {
		warnx("%s", errstr);
		return;
	}
	if (bsde_rule_to_string(&rule, charstr, BUFSIZ) == -1)
		warnx("Added rule, but unable to print string.");
	else
		printf("%d %s\n", rulenum, charstr);
}