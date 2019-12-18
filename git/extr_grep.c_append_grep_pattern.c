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
struct grep_opt {int dummy; } ;
typedef  enum grep_pat_token { ____Placeholder_grep_pat_token } grep_pat_token ;

/* Variables and functions */
 int /*<<< orphan*/  append_grep_pat (struct grep_opt*,char const*,int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void append_grep_pattern(struct grep_opt *opt, const char *pat,
			 const char *origin, int no, enum grep_pat_token t)
{
	append_grep_pat(opt, pat, strlen(pat), origin, no, t);
}