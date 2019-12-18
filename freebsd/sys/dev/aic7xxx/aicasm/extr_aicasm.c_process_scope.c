#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_8__ {int type; scalar_t__ begin_addr; scalar_t__ end_addr; int /*<<< orphan*/  inner_scope_patches; TYPE_1__* patches; int /*<<< orphan*/  inner_scope; } ;
typedef  TYPE_2__ scope_t ;
struct TYPE_7__ {scalar_t__ skip_instr; scalar_t__ skip_patch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
#define  SCOPE_ELSE 131 
#define  SCOPE_ELSE_IF 130 
#define  SCOPE_IF 129 
#define  SCOPE_ROOT 128 
 TYPE_2__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_PREV (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_links ; 
 int /*<<< orphan*/  scope_tailq ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 

void
process_scope(scope_t *scope)
{
	/*
	 * We are "leaving" this scope.  We should now have
	 * enough information to process the lists of scopes
	 * we encapsulate.
	 */
	scope_t *cur_scope;
	u_int skip_patch_count;
	u_int skip_instr_count;

	cur_scope = TAILQ_LAST(&scope->inner_scope, scope_tailq);
	skip_patch_count = 0;
	skip_instr_count = 0;
	while (cur_scope != NULL) {
		u_int patch0_patch_skip;

		patch0_patch_skip = 0;
		switch (cur_scope->type) {
		case SCOPE_IF:
		case SCOPE_ELSE_IF:
			if (skip_instr_count != 0) {
				/* Create a tail patch */
				patch0_patch_skip++;
				cur_scope->patches[1].skip_patch =
				    skip_patch_count + 1;
				cur_scope->patches[1].skip_instr =
				    skip_instr_count;
			}

			/* Count Head patch */
			patch0_patch_skip++;

			/* Count any patches contained in our inner scope */
			patch0_patch_skip += cur_scope->inner_scope_patches;

			cur_scope->patches[0].skip_patch = patch0_patch_skip;
			cur_scope->patches[0].skip_instr =
			    cur_scope->end_addr - cur_scope->begin_addr;

			skip_instr_count += cur_scope->patches[0].skip_instr;

			skip_patch_count += patch0_patch_skip;
			if (cur_scope->type == SCOPE_IF) {
				scope->inner_scope_patches += skip_patch_count;
				skip_patch_count = 0;
			        skip_instr_count = 0;
			}
			break;
		case SCOPE_ELSE:
			/* Count any patches contained in our innter scope */
			skip_patch_count += cur_scope->inner_scope_patches;

			skip_instr_count += cur_scope->end_addr
					  - cur_scope->begin_addr;
			break;
		case SCOPE_ROOT:
			stop("Unexpected scope type encountered", EX_SOFTWARE);
			/* NOTREACHED */
		}

		cur_scope = TAILQ_PREV(cur_scope, scope_tailq, scope_links);
	}
}