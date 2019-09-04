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
struct rebase_options {int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct option {struct rebase_options* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  REBASE_INTERACTIVE ; 
 int /*<<< orphan*/  REBASE_INTERACTIVE_EXPLICIT ; 

__attribute__((used)) static int parse_opt_interactive(const struct option *opt, const char *arg,
				 int unset)
{
	struct rebase_options *opts = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);

	opts->type = REBASE_INTERACTIVE;
	opts->flags |= REBASE_INTERACTIVE_EXPLICIT;

	return 0;
}