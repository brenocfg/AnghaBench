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
typedef  int reg_size_t ;
typedef  int /*<<< orphan*/  insn_size_t ;

/* Variables and functions */
 int EFAULT ; 
 int __get_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  access_ok (unsigned long,int) ; 

__attribute__((used)) static int read_opcode(reg_size_t pc, insn_size_t *result_opcode, int from_user_mode)
{
	int get_user_error;
	unsigned long aligned_pc;
	insn_size_t opcode;

	if ((pc & 3) == 1) {
		/* SHmedia */
		aligned_pc = pc & ~3;
		if (from_user_mode) {
			if (!access_ok(aligned_pc, sizeof(insn_size_t))) {
				get_user_error = -EFAULT;
			} else {
				get_user_error = __get_user(opcode, (insn_size_t *)aligned_pc);
				*result_opcode = opcode;
			}
			return get_user_error;
		} else {
			/* If the fault was in the kernel, we can either read
			 * this directly, or if not, we fault.
			*/
			*result_opcode = *(insn_size_t *)aligned_pc;
			return 0;
		}
	} else if ((pc & 1) == 0) {
		/* SHcompact */
		/* TODO : provide handling for this.  We don't really support
		   user-mode SHcompact yet, and for a kernel fault, this would
		   have to come from a module built for SHcompact.  */
		return -EFAULT;
	} else {
		/* misaligned */
		return -EFAULT;
	}
}