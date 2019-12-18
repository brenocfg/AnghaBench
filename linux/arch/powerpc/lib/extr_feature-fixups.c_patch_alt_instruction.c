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

/* Variables and functions */
 scalar_t__ branch_target (unsigned int*) ; 
 scalar_t__ instr_is_relative_branch (unsigned int) ; 
 int /*<<< orphan*/  raw_patch_instruction (unsigned int*,unsigned int) ; 
 unsigned int translate_branch (unsigned int*,unsigned int*) ; 

__attribute__((used)) static int patch_alt_instruction(unsigned int *src, unsigned int *dest,
				 unsigned int *alt_start, unsigned int *alt_end)
{
	unsigned int instr;

	instr = *src;

	if (instr_is_relative_branch(*src)) {
		unsigned int *target = (unsigned int *)branch_target(src);

		/* Branch within the section doesn't need translating */
		if (target < alt_start || target > alt_end) {
			instr = translate_branch(dest, src);
			if (!instr)
				return 1;
		}
	}

	raw_patch_instruction(dest, instr);

	return 0;
}