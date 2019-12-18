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

/* Variables and functions */
 int JUMP_CLASS_CLASS1 ; 
 int JUMP_TYPE_HALT ; 
 int /*<<< orphan*/  LDST_SRCDST_WORD_CLRW ; 
 int OP_ALG_AAI_RNG4_SK ; 
 int OP_ALG_AAI_SHIFT ; 
 int OP_ALG_ALGSEL_RNG ; 
 int OP_ALG_AS_INIT ; 
 int OP_TYPE_CLASS1_ALG ; 
 int* append_jump (int*,int) ; 
 int /*<<< orphan*/  append_load_imm_u32 (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_operation (int*,int) ; 
 int /*<<< orphan*/  init_job_desc (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_jump_tgt_here (int*,int*) ; 

__attribute__((used)) static void build_instantiation_desc(u32 *desc, int handle, int do_sk)
{
	u32 *jump_cmd, op_flags;

	init_job_desc(desc, 0);

	op_flags = OP_TYPE_CLASS1_ALG | OP_ALG_ALGSEL_RNG |
			(handle << OP_ALG_AAI_SHIFT) | OP_ALG_AS_INIT;

	/* INIT RNG in non-test mode */
	append_operation(desc, op_flags);

	if (!handle && do_sk) {
		/*
		 * For SH0, Secure Keys must be generated as well
		 */

		/* wait for done */
		jump_cmd = append_jump(desc, JUMP_CLASS_CLASS1);
		set_jump_tgt_here(desc, jump_cmd);

		/*
		 * load 1 to clear written reg:
		 * resets the done interrrupt and returns the RNG to idle.
		 */
		append_load_imm_u32(desc, 1, LDST_SRCDST_WORD_CLRW);

		/* Initialize State Handle  */
		append_operation(desc, OP_TYPE_CLASS1_ALG | OP_ALG_ALGSEL_RNG |
				 OP_ALG_AAI_RNG4_SK);
	}

	append_jump(desc, JUMP_CLASS_CLASS1 | JUMP_TYPE_HALT);
}