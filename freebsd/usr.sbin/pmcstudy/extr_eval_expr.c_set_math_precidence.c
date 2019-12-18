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
struct expression {scalar_t__ type; struct expression* next; } ;

/* Variables and functions */
 scalar_t__ TYPE_OP_DIVIDE ; 
 scalar_t__ TYPE_OP_MINUS ; 
 scalar_t__ TYPE_OP_MULT ; 
 scalar_t__ TYPE_OP_PLUS ; 
 scalar_t__ TYPE_PARN_CLOSE ; 
 scalar_t__ TYPE_PARN_OPEN ; 
 int /*<<< orphan*/  add_precendence (struct expression**,struct expression*,struct expression*) ; 

__attribute__((used)) static void
set_math_precidence(struct expression **beg, struct expression *exp, struct expression **stopped)
{
	struct expression *at, *start, *end;
	int cnt_lower, cnt_upper;
	/* 
	 * Walk through and set any math precedence to 
	 * get proper precedence we insert () around * / over + -
	 */
	end = NULL;
	start = at = exp;
	cnt_lower = cnt_upper = 0;
	while(at) { 
		if (at->type == TYPE_PARN_CLOSE) {
			/* Done with that paren */
			if (stopped) {
				*stopped = at;
			}
			if (cnt_lower && cnt_upper) {
				/* We have a mixed set ... add precedence between start/end */
				add_precendence(beg, start, end);
			}
			return;
		}
		if (at->type == TYPE_PARN_OPEN) {
			set_math_precidence(beg, at->next, &end);
			at = end;
			continue;
		} else if ((at->type == TYPE_OP_PLUS) ||
			   (at->type == TYPE_OP_MINUS)) {
			cnt_lower++;
		} else if ((at->type == TYPE_OP_DIVIDE) ||
			   (at->type == TYPE_OP_MULT)) {
			cnt_upper++;
		}
		at = at->next;
	}
	if (cnt_lower && cnt_upper) {
		add_precendence(beg, start, NULL);
	}
}