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
struct grep_pat {int token; struct grep_pat* pattern; int /*<<< orphan*/  regexp; int /*<<< orphan*/  pcre2_pattern; int /*<<< orphan*/  pcre1_regexp; struct grep_pat* next; } ;
struct grep_opt {int /*<<< orphan*/  pattern_expression; int /*<<< orphan*/  extended; struct grep_pat* pattern_list; } ;

/* Variables and functions */
#define  GREP_PATTERN 130 
#define  GREP_PATTERN_BODY 129 
#define  GREP_PATTERN_HEAD 128 
 int /*<<< orphan*/  free (struct grep_pat*) ; 
 int /*<<< orphan*/  free_pattern_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pcre1_regexp (struct grep_pat*) ; 
 int /*<<< orphan*/  free_pcre2_pattern (struct grep_pat*) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

void free_grep_patterns(struct grep_opt *opt)
{
	struct grep_pat *p, *n;

	for (p = opt->pattern_list; p; p = n) {
		n = p->next;
		switch (p->token) {
		case GREP_PATTERN: /* atom */
		case GREP_PATTERN_HEAD:
		case GREP_PATTERN_BODY:
			if (p->pcre1_regexp)
				free_pcre1_regexp(p);
			else if (p->pcre2_pattern)
				free_pcre2_pattern(p);
			else
				regfree(&p->regexp);
			free(p->pattern);
			break;
		default:
			break;
		}
		free(p);
	}

	if (!opt->extended)
		return;
	free_pattern_expr(opt->pattern_expression);
}