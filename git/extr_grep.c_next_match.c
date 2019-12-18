#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grep_pat {int token; struct grep_pat* next; } ;
struct grep_opt {struct grep_pat* pattern_list; } ;
struct TYPE_4__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  enum grep_context { ____Placeholder_grep_context } grep_context ;

/* Variables and functions */
#define  GREP_PATTERN 130 
#define  GREP_PATTERN_BODY 129 
#define  GREP_PATTERN_HEAD 128 
 int match_next_pattern (struct grep_pat*,char*,char*,int,TYPE_1__*,int) ; 

__attribute__((used)) static int next_match(struct grep_opt *opt, char *bol, char *eol,
		      enum grep_context ctx, regmatch_t *pmatch, int eflags)
{
	struct grep_pat *p;
	int hit = 0;

	pmatch->rm_so = pmatch->rm_eo = -1;
	if (bol < eol) {
		for (p = opt->pattern_list; p; p = p->next) {
			switch (p->token) {
			case GREP_PATTERN: /* atom */
			case GREP_PATTERN_HEAD:
			case GREP_PATTERN_BODY:
				hit |= match_next_pattern(p, bol, eol, ctx,
							  pmatch, eflags);
				break;
			default:
				break;
			}
		}
	}
	return hit;
}