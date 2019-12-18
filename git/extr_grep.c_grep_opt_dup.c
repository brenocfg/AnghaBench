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
struct grep_pat {scalar_t__ token; int /*<<< orphan*/  no; int /*<<< orphan*/  origin; int /*<<< orphan*/  patternlen; int /*<<< orphan*/  pattern; int /*<<< orphan*/  field; struct grep_pat* next; } ;
struct grep_opt {struct grep_pat* pattern_list; struct grep_pat** pattern_tail; } ;

/* Variables and functions */
 scalar_t__ GREP_PATTERN_HEAD ; 
 int /*<<< orphan*/  append_grep_pat (struct grep_opt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  append_header_grep_pattern (struct grep_opt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct grep_opt* xmalloc (int) ; 

struct grep_opt *grep_opt_dup(const struct grep_opt *opt)
{
	struct grep_pat *pat;
	struct grep_opt *ret = xmalloc(sizeof(struct grep_opt));
	*ret = *opt;

	ret->pattern_list = NULL;
	ret->pattern_tail = &ret->pattern_list;

	for(pat = opt->pattern_list; pat != NULL; pat = pat->next)
	{
		if(pat->token == GREP_PATTERN_HEAD)
			append_header_grep_pattern(ret, pat->field,
						   pat->pattern);
		else
			append_grep_pat(ret, pat->pattern, pat->patternlen,
					pat->origin, pat->no, pat->token);
	}

	return ret;
}