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
struct proc_handle {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFX (char*) ; 
 int /*<<< orphan*/  PT_STEP ; 
 int /*<<< orphan*/  REG_PC ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ proc_bkptdel (struct proc_handle*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  proc_bkptregadj (unsigned long*) ; 
 scalar_t__ proc_bkptset (struct proc_handle*,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 int proc_getwstat (struct proc_handle*) ; 
 scalar_t__ proc_regget (struct proc_handle*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  proc_regset (struct proc_handle*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  proc_wstatus (struct proc_handle*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_bkptexec(struct proc_handle *phdl, unsigned long saved)
{
	unsigned long pc;
	unsigned long samesaved;
	int status;

	if (proc_regget(phdl, REG_PC, &pc) < 0) {
		DPRINTFX("ERROR: couldn't get PC register");
		return (-1);
	}
	proc_bkptregadj(&pc);
	if (proc_bkptdel(phdl, pc, saved) < 0) {
		DPRINTFX("ERROR: couldn't delete breakpoint");
		return (-1);
	}
	/*
	 * Go back in time and step over the new instruction just
	 * set up by proc_bkptdel().
	 */
	proc_regset(phdl, REG_PC, pc);
	if (ptrace(PT_STEP, proc_getpid(phdl), (caddr_t)1, 0) < 0) {
		DPRINTFX("ERROR: ptrace step failed");
		return (-1);
	}
	proc_wstatus(phdl);
	status = proc_getwstat(phdl);
	if (!WIFSTOPPED(status)) {
		DPRINTFX("ERROR: don't know why process stopped");
		return (-1);
	}
	/*
	 * Restore the breakpoint. The saved instruction should be
	 * the same as the one that we were passed in.
	 */
	if (proc_bkptset(phdl, pc, &samesaved) < 0) {
		DPRINTFX("ERROR: couldn't restore breakpoint");
		return (-1);
	}
	assert(samesaved == saved);

	return (0);
}