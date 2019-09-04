#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grep_pat {struct grep_pat* next; } ;
struct grep_opt {int /*<<< orphan*/  columnnum; struct grep_pat* pattern_list; scalar_t__ extended; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {scalar_t__ rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  enum grep_context { ____Placeholder_grep_context } grep_context ;

/* Variables and functions */
 int match_expr (struct grep_opt*,char*,char*,int,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ match_one_pattern (struct grep_pat*,char*,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_line(struct grep_opt *opt, char *bol, char *eol,
		      ssize_t *col, ssize_t *icol,
		      enum grep_context ctx, int collect_hits)
{
	struct grep_pat *p;
	int hit = 0;

	if (opt->extended)
		return match_expr(opt, bol, eol, ctx, col, icol,
				  collect_hits);

	/* we do not call with collect_hits without being extended */
	for (p = opt->pattern_list; p; p = p->next) {
		regmatch_t tmp;
		if (match_one_pattern(p, bol, eol, ctx, &tmp, 0)) {
			hit |= 1;
			if (!opt->columnnum) {
				/*
				 * Without --column, any single match on a line
				 * is enough to know that it needs to be
				 * printed. With --column, scan _all_ patterns
				 * to find the earliest.
				 */
				break;
			}
			if (*col < 0 || tmp.rm_so < *col)
				*col = tmp.rm_so;
		}
	}
	return hit;
}