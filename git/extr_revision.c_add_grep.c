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
struct rev_info {int /*<<< orphan*/  grep_filter; } ;
typedef  enum grep_pat_token { ____Placeholder_grep_pat_token } grep_pat_token ;

/* Variables and functions */
 int /*<<< orphan*/  append_grep_pattern (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void add_grep(struct rev_info *revs, const char *ptn, enum grep_pat_token what)
{
	append_grep_pattern(&revs->grep_filter, ptn, "command line", 0, what);
}