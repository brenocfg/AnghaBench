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

/* Variables and functions */
 int GREP_PATTERN_TYPE_BRE ; 
 int GREP_PATTERN_TYPE_ERE ; 
 int GREP_PATTERN_TYPE_FIXED ; 
 int GREP_PATTERN_TYPE_PCRE ; 
 int GREP_PATTERN_TYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  die (char*,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int parse_pattern_type_arg(const char *opt, const char *arg)
{
	if (!strcmp(arg, "default"))
		return GREP_PATTERN_TYPE_UNSPECIFIED;
	else if (!strcmp(arg, "basic"))
		return GREP_PATTERN_TYPE_BRE;
	else if (!strcmp(arg, "extended"))
		return GREP_PATTERN_TYPE_ERE;
	else if (!strcmp(arg, "fixed"))
		return GREP_PATTERN_TYPE_FIXED;
	else if (!strcmp(arg, "perl"))
		return GREP_PATTERN_TYPE_PCRE;
	die("bad %s argument: %s", opt, arg);
}