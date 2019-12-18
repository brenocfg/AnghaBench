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
struct option {struct diff_options* value; } ;
struct diff_options {int /*<<< orphan*/  output_format; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  enable_patch_output (int /*<<< orphan*/ *) ; 
 int error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int) ; 

__attribute__((used)) static int diff_opt_unified(const struct option *opt,
			    const char *arg, int unset)
{
	struct diff_options *options = opt->value;
	char *s;

	BUG_ON_OPT_NEG(unset);

	if (arg) {
		options->context = strtol(arg, &s, 10);
		if (*s)
			return error(_("%s expects a numerical value"), "--unified");
	}
	enable_patch_output(&options->output_format);

	return 0;
}