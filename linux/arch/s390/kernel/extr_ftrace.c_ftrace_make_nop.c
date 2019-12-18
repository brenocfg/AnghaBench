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
struct module {int dummy; } ;
struct ftrace_insn {int dummy; } ;
struct dyn_ftrace {scalar_t__ ip; } ;
typedef  int /*<<< orphan*/  old ;
typedef  int /*<<< orphan*/  new ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 unsigned long MCOUNT_ADDR ; 
 int /*<<< orphan*/  ftrace_generate_call_insn (struct ftrace_insn*,scalar_t__) ; 
 int /*<<< orphan*/  ftrace_generate_kprobe_call_insn (struct ftrace_insn*) ; 
 int /*<<< orphan*/  ftrace_generate_kprobe_nop_insn (struct ftrace_insn*) ; 
 int /*<<< orphan*/  ftrace_generate_nop_insn (struct ftrace_insn*) ; 
 int /*<<< orphan*/  ftrace_generate_orig_insn (struct ftrace_insn*) ; 
 scalar_t__ is_kprobe_on_ftrace (struct ftrace_insn*) ; 
 scalar_t__ memcmp (struct ftrace_insn*,struct ftrace_insn*,int) ; 
 scalar_t__ probe_kernel_read (struct ftrace_insn*,void*,int) ; 
 int /*<<< orphan*/  s390_kernel_write (void*,struct ftrace_insn*,int) ; 

int ftrace_make_nop(struct module *mod, struct dyn_ftrace *rec,
		    unsigned long addr)
{
	struct ftrace_insn orig, new, old;

	if (probe_kernel_read(&old, (void *) rec->ip, sizeof(old)))
		return -EFAULT;
	if (addr == MCOUNT_ADDR) {
		/* Initial code replacement */
		ftrace_generate_orig_insn(&orig);
		ftrace_generate_nop_insn(&new);
	} else if (is_kprobe_on_ftrace(&old)) {
		/*
		 * If we find a breakpoint instruction, a kprobe has been
		 * placed at the beginning of the function. We write the
		 * constant KPROBE_ON_FTRACE_NOP into the remaining four
		 * bytes of the original instruction so that the kprobes
		 * handler can execute a nop, if it reaches this breakpoint.
		 */
		ftrace_generate_kprobe_call_insn(&orig);
		ftrace_generate_kprobe_nop_insn(&new);
	} else {
		/* Replace ftrace call with a nop. */
		ftrace_generate_call_insn(&orig, rec->ip);
		ftrace_generate_nop_insn(&new);
	}
	/* Verify that the to be replaced code matches what we expect. */
	if (memcmp(&orig, &old, sizeof(old)))
		return -EINVAL;
	s390_kernel_write((void *) rec->ip, &new, sizeof(new));
	return 0;
}