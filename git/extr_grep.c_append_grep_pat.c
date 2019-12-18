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
struct grep_pat {int dummy; } ;
struct grep_opt {int /*<<< orphan*/  pattern_tail; } ;
typedef  enum grep_pat_token { ____Placeholder_grep_pat_token } grep_pat_token ;

/* Variables and functions */
 struct grep_pat* create_grep_pat (char const*,size_t,char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_append_grep_pat (int /*<<< orphan*/ *,struct grep_pat*) ; 

void append_grep_pat(struct grep_opt *opt, const char *pat, size_t patlen,
		     const char *origin, int no, enum grep_pat_token t)
{
	struct grep_pat *p = create_grep_pat(pat, patlen, origin, no, t, 0);
	do_append_grep_pat(&opt->pattern_tail, p);
}