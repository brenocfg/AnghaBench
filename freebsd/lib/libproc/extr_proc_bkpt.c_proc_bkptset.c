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
typedef  int /*<<< orphan*/  uintmax_t ;
struct ptrace_io_desc {unsigned long* piod_addr; void* piod_len; void* piod_offs; int /*<<< orphan*/  piod_op; } ;
struct proc_handle {scalar_t__ status; } ;
typedef  unsigned long instr_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 unsigned long BREAKPOINT_INSTR ; 
 void* BREAKPOINT_INSTR_SZ ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFX (char*,uintptr_t) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  PIOD_READ_I ; 
 int /*<<< orphan*/  PIOD_WRITE_I ; 
 scalar_t__ PS_DEAD ; 
 scalar_t__ PS_IDLE ; 
 scalar_t__ PS_STOP ; 
 scalar_t__ PS_UNDEAD ; 
 int /*<<< orphan*/  PT_IO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  proc_continue (struct proc_handle*) ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 scalar_t__ proc_stop (struct proc_handle*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_bkptset(struct proc_handle *phdl, uintptr_t address,
    unsigned long *saved)
{
	struct ptrace_io_desc piod;
	int ret = 0, stopped;
	instr_t instr;

	*saved = 0;
	if (phdl->status == PS_DEAD || phdl->status == PS_UNDEAD ||
	    phdl->status == PS_IDLE) {
		errno = ENOENT;
		return (-1);
	}

	DPRINTFX("adding breakpoint at 0x%lx", address);

	stopped = 0;
	if (phdl->status != PS_STOP) {
		if (proc_stop(phdl) != 0)
			return (-1);
		stopped = 1;
	}

	/*
	 * Read the original instruction.
	 */
	instr = 0;
	piod.piod_op = PIOD_READ_I;
	piod.piod_offs = (void *)address;
	piod.piod_addr = &instr;
	piod.piod_len  = BREAKPOINT_INSTR_SZ;
	if (ptrace(PT_IO, proc_getpid(phdl), (caddr_t)&piod, 0) < 0) {
		DPRINTF("ERROR: couldn't read instruction at address 0x%jx",
		    (uintmax_t)address);
		ret = -1;
		goto done;
	}
	*saved = instr;
	/*
	 * Write a breakpoint instruction to that address.
	 */
	instr = BREAKPOINT_INSTR;
	piod.piod_op = PIOD_WRITE_I;
	piod.piod_offs = (void *)address;
	piod.piod_addr = &instr;
	piod.piod_len  = BREAKPOINT_INSTR_SZ;
	if (ptrace(PT_IO, proc_getpid(phdl), (caddr_t)&piod, 0) < 0) {
		DPRINTF("ERROR: couldn't write instruction at address 0x%jx",
		    (uintmax_t)address);
		ret = -1;
		goto done;
	}

done:
	if (stopped)
		/* Restart the process if we had to stop it. */
		proc_continue(phdl);

	return (ret);
}