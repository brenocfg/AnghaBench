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
struct option {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 scalar_t__ auto_number ; 
 int numbered_cmdline_opt ; 

__attribute__((used)) static int numbered_callback(const struct option *opt, const char *arg,
			     int unset)
{
	BUG_ON_OPT_ARG(arg);
	*(int *)opt->value = numbered_cmdline_opt = unset ? 0 : 1;
	if (unset)
		auto_number =  0;
	return 0;
}