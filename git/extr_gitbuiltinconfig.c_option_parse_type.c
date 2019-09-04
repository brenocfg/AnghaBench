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
struct option {int* value; int defval; } ;

/* Variables and functions */
 int TYPE_BOOL ; 
 int TYPE_BOOL_OR_INT ; 
 int TYPE_COLOR ; 
 int TYPE_EXPIRY_DATE ; 
 int TYPE_INT ; 
 int TYPE_PATH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage_builtin_config () ; 

__attribute__((used)) static int option_parse_type(const struct option *opt, const char *arg,
			     int unset)
{
	int new_type, *to_type;

	if (unset) {
		*((int *) opt->value) = 0;
		return 0;
	}

	/*
	 * To support '--<type>' style flags, begin with new_type equal to
	 * opt->defval.
	 */
	new_type = opt->defval;
	if (!new_type) {
		if (!strcmp(arg, "bool"))
			new_type = TYPE_BOOL;
		else if (!strcmp(arg, "int"))
			new_type = TYPE_INT;
		else if (!strcmp(arg, "bool-or-int"))
			new_type = TYPE_BOOL_OR_INT;
		else if (!strcmp(arg, "path"))
			new_type = TYPE_PATH;
		else if (!strcmp(arg, "expiry-date"))
			new_type = TYPE_EXPIRY_DATE;
		else if (!strcmp(arg, "color"))
			new_type = TYPE_COLOR;
		else
			die(_("unrecognized --type argument, %s"), arg);
	}

	to_type = opt->value;
	if (*to_type && *to_type != new_type) {
		/*
		 * Complain when there is a new type not equal to the old type.
		 * This allows for combinations like '--int --type=int' and
		 * '--type=int --type=int', but disallows ones like '--type=bool
		 * --int' and '--type=bool
		 * --type=int'.
		 */
		error(_("only one type at a time"));
		usage_builtin_config();
	}
	*to_type = new_type;

	return 0;
}