#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  assignment; } ;
struct assignment {int /*<<< orphan*/  name; TYPE_1__ u; struct assignment* next; } ;

/* Variables and functions */
 scalar_t__ check_option (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex (struct assignment*,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
check_command(struct assignment *as)
{
	struct assignment *a;
	int seen_name = 0;
	int seen_function = 0;
	int seen_help = 0;
	int seen_argument = 0;
	int seen_minargs = 0;
	int seen_maxargs = 0;
	int ret = 0;
	for(a = as; a != NULL; a = a->next) {
		if(strcmp(a->name, "name") == 0)
			seen_name++;
		else if(strcmp(a->name, "function") == 0) {
			seen_function++;
		} else if(strcmp(a->name, "option") == 0)
			ret += check_option(a->u.assignment);
		else if(strcmp(a->name, "help") == 0) {
			seen_help++;
		} else if(strcmp(a->name, "argument") == 0) {
			seen_argument++;
		} else if(strcmp(a->name, "min_args") == 0) {
			seen_minargs++;
		} else if(strcmp(a->name, "max_args") == 0) {
			seen_maxargs++;
		} else {
			ex(a, "unknown name: %s", a->name);
			ret++;
		}
	}
	if(seen_name == 0) {
		ex(as, "no command name");
		ret++;
	}
	if(seen_function > 1) {
		ex(as, "multiple function names");
		ret++;
	}
	if(seen_help > 1) {
		ex(as, "multiple help strings");
		ret++;
	}
	if(seen_argument > 1) {
		ex(as, "multiple argument strings");
		ret++;
	}
	if(seen_minargs > 1) {
		ex(as, "multiple min_args strings");
		ret++;
	}
	if(seen_maxargs > 1) {
		ex(as, "multiple max_args strings");
		ret++;
	}

	return ret;
}