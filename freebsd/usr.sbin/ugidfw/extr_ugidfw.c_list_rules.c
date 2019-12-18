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
 int bsde_get_rule (int,struct mac_bsdextended_rule*,int,char*) ; 
 int bsde_get_rule_count (int,char*) ; 
 int bsde_get_rule_slots (int,char*) ; 
 int bsde_rule_to_string (struct mac_bsdextended_rule*,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
list_rules(void)
{
	char errstr[BUFSIZ], charstr[BUFSIZ];
	struct mac_bsdextended_rule rule;
	int error, i, rule_count, rule_slots;

	rule_slots = bsde_get_rule_slots(BUFSIZ, errstr);
	if (rule_slots == -1) {
		warnx("unable to get rule slots; mac_bsdextended.ko "
		    "may not be loaded");
		errx(1, "bsde_get_rule_slots: %s", errstr);
	}

	rule_count = bsde_get_rule_count(BUFSIZ, errstr);
	if (rule_count == -1)
		errx(1, "bsde_get_rule_count: %s", errstr);

	printf("%d slots, %d rules\n", rule_slots, rule_count);

	for (i = 0; i < rule_slots; i++) {
		error = bsde_get_rule(i, &rule, BUFSIZ, errstr);
		switch (error) {
		case -2:
			continue;
		case -1:
			warnx("rule %d: %s", i, errstr);
			continue;
		case 0:
			break;
		}

		if (bsde_rule_to_string(&rule, charstr, BUFSIZ) == -1)
			warnx("unable to translate rule %d to string", i);
		else
			printf("%d %s\n", i, charstr);
	}
}