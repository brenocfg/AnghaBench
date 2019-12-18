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
struct proc_handle {int /*<<< orphan*/  status; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__) ; 
 int /*<<< orphan*/  DPRINTFX (char*,scalar_t__,int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int PATTACH_NOSTOP ; 
 int PATTACH_RDONLY ; 
 int /*<<< orphan*/  PS_RUN ; 
 int /*<<< orphan*/  PS_STOP ; 
 int /*<<< orphan*/  PT_ATTACH ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  proc_continue (struct proc_handle*) ; 
 int /*<<< orphan*/  proc_free (struct proc_handle*) ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 int proc_init (scalar_t__,int,int /*<<< orphan*/ ,struct proc_handle**) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int
proc_attach(pid_t pid, int flags, struct proc_handle **pphdl)
{
	struct proc_handle *phdl;
	int error, status;

	if (pid == 0 || (pid == getpid() && (flags & PATTACH_RDONLY) == 0))
		return (EINVAL);
	if (elf_version(EV_CURRENT) == EV_NONE)
		return (ENOENT);

	/*
	 * Allocate memory for the process handle, a structure containing
	 * all things related to the process.
	 */
	error = proc_init(pid, flags, PS_RUN, &phdl);
	if (error != 0)
		goto out;

	if ((flags & PATTACH_RDONLY) == 0) {
		if (ptrace(PT_ATTACH, proc_getpid(phdl), 0, 0) != 0) {
			error = errno;
			DPRINTF("ERROR: cannot ptrace child process %d", pid);
			goto out;
		}

		/* Wait for the child process to stop. */
		if (waitpid(pid, &status, WUNTRACED) == -1) {
			error = errno;
			DPRINTF("ERROR: child process %d didn't stop as expected", pid);
			goto out;
		}

		/* Check for an unexpected status. */
		if (!WIFSTOPPED(status))
			DPRINTFX("ERROR: child process %d status 0x%x", pid, status);
		else
			phdl->status = PS_STOP;

		if ((flags & PATTACH_NOSTOP) != 0)
			proc_continue(phdl);
	}

out:
	if (error != 0 && phdl != NULL) {
		proc_free(phdl);
		phdl = NULL;
	}
	*pphdl = phdl;
	return (error);
}