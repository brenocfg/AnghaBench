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
struct diff_options {int /*<<< orphan*/  parseopts; } ;

/* Variables and functions */
 int PARSE_OPT_KEEP_DASHDASH ; 
 int PARSE_OPT_KEEP_UNKNOWN ; 
 int PARSE_OPT_NO_INTERNAL_HELP ; 
 int PARSE_OPT_ONE_SHOT ; 
 int PARSE_OPT_STOP_AT_NON_OPTION ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int diff_opt_parse(struct diff_options *options,
		   const char **av, int ac, const char *prefix)
{
	if (!prefix)
		prefix = "";

	ac = parse_options(ac, av, prefix, options->parseopts, NULL,
			   PARSE_OPT_KEEP_DASHDASH |
			   PARSE_OPT_KEEP_UNKNOWN |
			   PARSE_OPT_NO_INTERNAL_HELP |
			   PARSE_OPT_ONE_SHOT |
			   PARSE_OPT_STOP_AT_NON_OPTION);

	return ac;
}