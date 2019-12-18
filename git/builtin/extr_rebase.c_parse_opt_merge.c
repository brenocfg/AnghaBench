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
struct rebase_options {int /*<<< orphan*/  type; } ;
struct option {struct rebase_options* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  REBASE_MERGE ; 
 int /*<<< orphan*/  is_interactive (struct rebase_options*) ; 

__attribute__((used)) static int parse_opt_merge(const struct option *opt, const char *arg, int unset)
{
	struct rebase_options *opts = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);

	if (!is_interactive(opts))
		opts->type = REBASE_MERGE;

	return 0;
}