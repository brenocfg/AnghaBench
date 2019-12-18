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
struct rulehead {int dummy; } ;
struct rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct rulehead*,struct rule*,int /*<<< orphan*/ ) ; 
 int parse_rule_element (char*,struct rule**) ; 
 int /*<<< orphan*/  r_entries ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  toast_rules (struct rulehead*) ; 

__attribute__((used)) static int
parse_rules(char *string, struct rulehead *head)
{
	struct rule *new;
	char *element;
	int error;

	error = 0;
	while ((element = strsep(&string, ",")) != NULL) {
		if (strlen(element) == 0)
			continue;
		error = parse_rule_element(element, &new);
		if (error)
			goto out;
		TAILQ_INSERT_TAIL(head, new, r_entries);
	}
out:
	if (error != 0)
		toast_rules(head);
	return (error);
}