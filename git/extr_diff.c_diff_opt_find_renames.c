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
struct diff_options {int /*<<< orphan*/  detect_rename; int /*<<< orphan*/  rename_score; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  DIFF_DETECT_RENAME ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_rename_score (char const**) ; 

__attribute__((used)) static int diff_opt_find_renames(const struct option *opt,
				 const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	options->rename_score = parse_rename_score(&arg);
	if (*arg != 0)
		return error(_("invalid argument to %s"), opt->long_name);

	options->detect_rename = DIFF_DETECT_RENAME;
	return 0;
}