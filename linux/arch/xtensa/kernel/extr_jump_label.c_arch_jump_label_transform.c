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
typedef  int u32 ;
struct jump_entry {int dummy; } ;
typedef  enum jump_label_type { ____Placeholder_jump_label_type } jump_label_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int JUMP_LABEL_JMP ; 
 int /*<<< orphan*/  JUMP_LABEL_NOP_SIZE ; 
 int J_INSN ; 
 int J_OFFSET_MASK ; 
 int J_SIGN_MASK ; 
 int NOP_INSN ; 
 int jump_entry_code (struct jump_entry*) ; 
 int jump_entry_target (struct jump_entry*) ; 
 int /*<<< orphan*/  patch_text (int,int*,int /*<<< orphan*/ ) ; 

void arch_jump_label_transform(struct jump_entry *e,
			       enum jump_label_type type)
{
	u32 d = (jump_entry_target(e) - (jump_entry_code(e) + 4));
	u32 insn;

	/* Jump only works within 128K of the J instruction. */
	BUG_ON(!((d & J_SIGN_MASK) == 0 ||
		 (d & J_SIGN_MASK) == J_SIGN_MASK));

	if (type == JUMP_LABEL_JMP) {
#if defined(__XTENSA_EL__)
		insn = ((d & J_OFFSET_MASK) << 6) | J_INSN;
#elif defined(__XTENSA_EB__)
		insn = ((d & J_OFFSET_MASK) << 8) | J_INSN;
#endif
	} else {
		insn = NOP_INSN;
	}

	patch_text(jump_entry_code(e), &insn, JUMP_LABEL_NOP_SIZE);
}