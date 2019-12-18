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
struct jump_entry {int /*<<< orphan*/  target; scalar_t__ code; } ;
typedef  enum jump_label_type { ____Placeholder_jump_label_type } jump_label_type ;

/* Variables and functions */
 int JUMP_LABEL_JMP ; 
 int /*<<< orphan*/  __patch_text_early (void*,unsigned int) ; 
 unsigned int arm_gen_branch (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int arm_gen_nop () ; 
 int /*<<< orphan*/  patch_text (void*,unsigned int) ; 

__attribute__((used)) static void __arch_jump_label_transform(struct jump_entry *entry,
					enum jump_label_type type,
					bool is_static)
{
	void *addr = (void *)entry->code;
	unsigned int insn;

	if (type == JUMP_LABEL_JMP)
		insn = arm_gen_branch(entry->code, entry->target);
	else
		insn = arm_gen_nop();

	if (is_static)
		__patch_text_early(addr, insn);
	else
		patch_text(addr, insn);
}