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
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 scalar_t__ DEFAULT_REFLOG ; 
 int error (char*,char const*) ; 
 scalar_t__ reflog ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static int parse_reflog_param(const struct option *opt, const char *arg,
			      int unset)
{
	char *ep;
	const char **base = (const char **)opt->value;
	BUG_ON_OPT_NEG(unset);
	if (!arg)
		arg = "";
	reflog = strtoul(arg, &ep, 10);
	if (*ep == ',')
		*base = ep + 1;
	else if (*ep)
		return error("unrecognized reflog param '%s'", arg);
	else
		*base = NULL;
	if (reflog <= 0)
		reflog = DEFAULT_REFLOG;
	return 0;
}