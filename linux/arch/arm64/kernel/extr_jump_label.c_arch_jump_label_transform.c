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
typedef  int /*<<< orphan*/  u32 ;
struct jump_entry {int dummy; } ;
typedef  enum jump_label_type { ____Placeholder_jump_label_type } jump_label_type ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_BRANCH_NOLINK ; 
 int JUMP_LABEL_JMP ; 
 int /*<<< orphan*/  aarch64_insn_gen_branch_imm (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aarch64_insn_gen_nop () ; 
 int /*<<< orphan*/  aarch64_insn_patch_text_nosync (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ jump_entry_code (struct jump_entry*) ; 
 int /*<<< orphan*/  jump_entry_target (struct jump_entry*) ; 

void arch_jump_label_transform(struct jump_entry *entry,
			       enum jump_label_type type)
{
	void *addr = (void *)jump_entry_code(entry);
	u32 insn;

	if (type == JUMP_LABEL_JMP) {
		insn = aarch64_insn_gen_branch_imm(jump_entry_code(entry),
						   jump_entry_target(entry),
						   AARCH64_INSN_BRANCH_NOLINK);
	} else {
		insn = aarch64_insn_gen_nop();
	}

	aarch64_insn_patch_text_nosync(addr, insn);
}