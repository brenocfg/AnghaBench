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
struct grep_pat {int token; int /*<<< orphan*/  pattern; struct grep_pat* next; } ;
struct grep_opt {int extended; int all_match; struct grep_expr* pattern_expression; struct grep_pat* pattern_list; int /*<<< orphan*/  debug; } ;
struct grep_expr {int dummy; } ;

/* Variables and functions */
#define  GREP_PATTERN 130 
#define  GREP_PATTERN_BODY 129 
#define  GREP_PATTERN_HEAD 128 
 struct grep_expr* compile_pattern_expr (struct grep_pat**) ; 
 int /*<<< orphan*/  compile_regexp (struct grep_pat*,struct grep_opt*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 struct grep_expr* grep_or_expr (struct grep_expr*,struct grep_expr*) ; 
 struct grep_expr* grep_splice_or (struct grep_expr*,struct grep_expr*) ; 
 struct grep_expr* prep_header_patterns (struct grep_opt*) ; 

__attribute__((used)) static void compile_grep_patterns_real(struct grep_opt *opt)
{
	struct grep_pat *p;
	struct grep_expr *header_expr = prep_header_patterns(opt);

	for (p = opt->pattern_list; p; p = p->next) {
		switch (p->token) {
		case GREP_PATTERN: /* atom */
		case GREP_PATTERN_HEAD:
		case GREP_PATTERN_BODY:
			compile_regexp(p, opt);
			break;
		default:
			opt->extended = 1;
			break;
		}
	}

	if (opt->all_match || header_expr)
		opt->extended = 1;
	else if (!opt->extended && !opt->debug)
		return;

	p = opt->pattern_list;
	if (p)
		opt->pattern_expression = compile_pattern_expr(&p);
	if (p)
		die("incomplete pattern expression: %s", p->pattern);

	if (!header_expr)
		return;

	if (!opt->pattern_expression)
		opt->pattern_expression = header_expr;
	else if (opt->all_match)
		opt->pattern_expression = grep_splice_or(header_expr,
							 opt->pattern_expression);
	else
		opt->pattern_expression = grep_or_expr(opt->pattern_expression,
						       header_expr);
	opt->all_match = 1;
}