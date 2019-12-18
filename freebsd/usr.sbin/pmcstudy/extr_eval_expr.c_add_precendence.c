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
 scalar_t__ TYPE_OP_MULT ; 
 scalar_t__ TYPE_PARN_CLOSE ; 
 scalar_t__ TYPE_PARN_OPEN ; 
 int /*<<< orphan*/  walk_back_and_insert_paren (struct expression**,struct expression*) ; 
 int /*<<< orphan*/  walk_fwd_and_insert_paren (struct expression*,struct expression**) ; 

__attribute__((used)) static void
add_precendence(struct expression **beg, struct expression *start, struct expression *end)
{
	/* 
	 * Between start and end add () around any * or /. This
	 * is quite tricky since if there is a () set inside the
	 * list we need to skip over everything in the ()'s considering
	 * that just a value.
	 */
	struct expression *at, *newone;
	int open_cnt;

	at = start;
	open_cnt = 0;
	while(at != end) {
		if (at->type == TYPE_PARN_OPEN) {
			open_cnt++;
		}
		if (at->type == TYPE_PARN_CLOSE) {
			open_cnt--;
		}
		if (open_cnt == 0) {
			if ((at->type == TYPE_OP_MULT) ||
			    (at->type == TYPE_OP_DIVIDE)) {
				walk_back_and_insert_paren(beg, at);
				walk_fwd_and_insert_paren(at, &newone);
				at = newone->next;
				continue;
			}
		}
		at = at->next;
	}
	
}