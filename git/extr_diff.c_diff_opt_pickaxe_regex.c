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
struct diff_options {char const* pickaxe; int /*<<< orphan*/  pickaxe_opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  DIFF_PICKAXE_KIND_G ; 

__attribute__((used)) static int diff_opt_pickaxe_regex(const struct option *opt,
				  const char *arg, int unset)
{
	struct diff_options *options = opt->value;

	BUG_ON_OPT_NEG(unset);
	options->pickaxe = arg;
	options->pickaxe_opts |= DIFF_PICKAXE_KIND_G;
	return 0;
}