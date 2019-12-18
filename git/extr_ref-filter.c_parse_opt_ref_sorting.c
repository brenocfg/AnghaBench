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
struct option {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  parse_ref_sorting (int /*<<< orphan*/ ,char const*) ; 

int parse_opt_ref_sorting(const struct option *opt, const char *arg, int unset)
{
	/*
	 * NEEDSWORK: We should probably clear the list in this case, but we've
	 * already munged the global used_atoms list, which would need to be
	 * undone.
	 */
	BUG_ON_OPT_NEG(unset);

	parse_ref_sorting(opt->value, arg);
	return 0;
}