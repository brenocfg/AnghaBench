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
struct option {struct grep_opt* value; } ;
struct grep_opt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON_OPT_ARG (char const*) ; 
 int /*<<< orphan*/  BUG_ON_OPT_NEG (int) ; 
 int /*<<< orphan*/  GREP_NOT ; 
 int /*<<< orphan*/  append_grep_pattern (struct grep_opt*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int not_callback(const struct option *opt, const char *arg, int unset)
{
	struct grep_opt *grep_opt = opt->value;
	BUG_ON_OPT_NEG(unset);
	BUG_ON_OPT_ARG(arg);
	append_grep_pattern(grep_opt, "--not", "command line", 0, GREP_NOT);
	return 0;
}