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
struct grep_opt {int pattern_type_option; scalar_t__ extended_regexp_option; } ;
typedef  enum grep_pattern_type { ____Placeholder_grep_pattern_type } grep_pattern_type ;

/* Variables and functions */
 int GREP_PATTERN_TYPE_ERE ; 
 int GREP_PATTERN_TYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  grep_set_pattern_type_option (int,struct grep_opt*) ; 

void grep_commit_pattern_type(enum grep_pattern_type pattern_type, struct grep_opt *opt)
{
	if (pattern_type != GREP_PATTERN_TYPE_UNSPECIFIED)
		grep_set_pattern_type_option(pattern_type, opt);
	else if (opt->pattern_type_option != GREP_PATTERN_TYPE_UNSPECIFIED)
		grep_set_pattern_type_option(opt->pattern_type_option, opt);
	else if (opt->extended_regexp_option)
		/*
		 * This branch *must* happen after setting from the
		 * opt->pattern_type_option above, we don't want
		 * grep.extendedRegexp to override grep.patternType!
		 */
		grep_set_pattern_type_option(GREP_PATTERN_TYPE_ERE, opt);
}