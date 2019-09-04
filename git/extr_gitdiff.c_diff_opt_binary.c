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
struct option {struct diff_options* value; } ;
struct TYPE_2__ {int binary; } ;
struct diff_options {TYPE_1__ flags; int /*<<< orphan*/  output_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  enable_patch_output (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diff_opt_binary(const struct option *opt,
			   const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);
	enable_patch_output(&options->output_format);
	options->flags.binary = 1;
	return 0;
}