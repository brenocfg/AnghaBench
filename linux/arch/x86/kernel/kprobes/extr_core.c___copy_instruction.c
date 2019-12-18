#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {scalar_t__* bytes; } ;
struct insn {int length; TYPE_2__ displacement; TYPE_1__ opcode; } ;
typedef  int s64 ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 scalar_t__ BREAKPOINT_INSTRUCTION ; 
 int MAX_INSN_SIZE ; 
 int /*<<< orphan*/  insn_get_length (struct insn*) ; 
 scalar_t__ insn_masking_exception (struct insn*) ; 
 int insn_offset_displacement (struct insn*) ; 
 scalar_t__ insn_rip_relative (struct insn*) ; 
 int /*<<< orphan*/  kernel_insn_init (struct insn*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ probe_kernel_read (int /*<<< orphan*/ *,void*,int) ; 
 unsigned long recover_probed_instruction (int /*<<< orphan*/ *,unsigned long) ; 

int __copy_instruction(u8 *dest, u8 *src, u8 *real, struct insn *insn)
{
	kprobe_opcode_t buf[MAX_INSN_SIZE];
	unsigned long recovered_insn =
		recover_probed_instruction(buf, (unsigned long)src);

	if (!recovered_insn || !insn)
		return 0;

	/* This can access kernel text if given address is not recovered */
	if (probe_kernel_read(dest, (void *)recovered_insn, MAX_INSN_SIZE))
		return 0;

	kernel_insn_init(insn, dest, MAX_INSN_SIZE);
	insn_get_length(insn);

	/* Another subsystem puts a breakpoint, failed to recover */
	if (insn->opcode.bytes[0] == BREAKPOINT_INSTRUCTION)
		return 0;

	/* We should not singlestep on the exception masking instructions */
	if (insn_masking_exception(insn))
		return 0;

#ifdef CONFIG_X86_64
	/* Only x86_64 has RIP relative instructions */
	if (insn_rip_relative(insn)) {
		s64 newdisp;
		u8 *disp;
		/*
		 * The copied instruction uses the %rip-relative addressing
		 * mode.  Adjust the displacement for the difference between
		 * the original location of this instruction and the location
		 * of the copy that will actually be run.  The tricky bit here
		 * is making sure that the sign extension happens correctly in
		 * this calculation, since we need a signed 32-bit result to
		 * be sign-extended to 64 bits when it's added to the %rip
		 * value and yield the same 64-bit result that the sign-
		 * extension of the original signed 32-bit displacement would
		 * have given.
		 */
		newdisp = (u8 *) src + (s64) insn->displacement.value
			  - (u8 *) real;
		if ((s64) (s32) newdisp != newdisp) {
			pr_err("Kprobes error: new displacement does not fit into s32 (%llx)\n", newdisp);
			return 0;
		}
		disp = (u8 *) dest + insn_offset_displacement(insn);
		*(s32 *) disp = (s32) newdisp;
	}
#endif
	return insn->length;
}