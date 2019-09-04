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
struct option {int /*<<< orphan*/  long_name; struct diff_options* value; } ;
struct diff_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  parse_dirstat_opt (struct diff_options*,char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int diff_opt_dirstat(const struct option *opt,
			    const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!strcmp(opt->long_name, "cumulative")) {
		if (arg)
			BUG("how come --cumulative take a value?");
		arg = "cumulative";
	} else if (!strcmp(opt->long_name, "dirstat-by-file"))
		parse_dirstat_opt(options, "files");
	parse_dirstat_opt(options, arg ? arg : "");
	return 0;
}