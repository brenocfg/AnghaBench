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
struct grep_pat {scalar_t__ token; struct grep_pat* next; } ;
struct grep_opt {struct grep_pat* pattern_list; scalar_t__ invert; scalar_t__ extended; } ;

/* Variables and functions */
 scalar_t__ GREP_PATTERN ; 

__attribute__((used)) static int should_lookahead(struct grep_opt *opt)
{
	struct grep_pat *p;

	if (opt->extended)
		return 0; /* punt for too complex stuff */
	if (opt->invert)
		return 0;
	for (p = opt->pattern_list; p; p = p->next) {
		if (p->token != GREP_PATTERN)
			return 0; /* punt for "header only" and stuff */
	}
	return 1;
}