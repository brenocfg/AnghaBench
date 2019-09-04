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
struct grep_opt {int use_reflog_filter; int /*<<< orphan*/  header_tail; } ;
typedef  enum grep_header_field { ____Placeholder_grep_header_field } grep_header_field ;

/* Variables and functions */
 int GREP_HEADER_REFLOG ; 
 int /*<<< orphan*/  GREP_PATTERN_HEAD ; 
 struct grep_pat* create_grep_pat (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_append_grep_pat (int /*<<< orphan*/ *,struct grep_pat*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void append_header_grep_pattern(struct grep_opt *opt,
				enum grep_header_field field, const char *pat)
{
	struct grep_pat *p = create_grep_pat(pat, strlen(pat), "header", 0,
					     GREP_PATTERN_HEAD, field);
	if (field == GREP_HEADER_REFLOG)
		opt->use_reflog_filter = 1;
	do_append_grep_pat(&opt->header_tail, p);
}