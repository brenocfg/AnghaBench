#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int begin; size_t patch_func; unsigned int skip_instr; int skip_patch; } ;
typedef  TYPE_1__ patch_t ;

/* Variables and functions */
 TYPE_1__* STAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 

__attribute__((used)) static int
check_patch(patch_t **start_patch, unsigned int start_instr,
	    unsigned int *skip_addr, int *func_vals)
{
	patch_t *cur_patch;

	cur_patch = *start_patch;

	while (cur_patch != NULL && start_instr == cur_patch->begin) {
		if (func_vals[cur_patch->patch_func] == 0) {
			int skip;

			/* Start rejecting code */
			*skip_addr = start_instr + cur_patch->skip_instr;
			for (skip = cur_patch->skip_patch;
			     skip > 0 && cur_patch != NULL;
			     skip--)
				cur_patch = STAILQ_NEXT(cur_patch, links);
		} else {
			/* Accepted this patch.  Advance to the next
			 * one and wait for our instruction pointer to
			 * hit this point.
			 */
			cur_patch = STAILQ_NEXT(cur_patch, links);
		}
	}

	*start_patch = cur_patch;
	if (start_instr < *skip_addr)
		/* Still skipping */
		return (0);

	return (1);
}