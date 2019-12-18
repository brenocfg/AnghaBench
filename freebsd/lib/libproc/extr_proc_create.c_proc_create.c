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
typedef  int /*<<< orphan*/  (* proc_child_func ) (void*) ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  DPRINTFX (char*,int,int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  PS_IDLE ; 
 int /*<<< orphan*/  PS_STOP ; 
 int /*<<< orphan*/  PT_TRACE_ME ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ elf_version (int /*<<< orphan*/ ) ; 
 char* const* environ ; 
 int errno ; 
 int /*<<< orphan*/  execvp (char const*,char* const*) ; 
 int fork () ; 
 int /*<<< orphan*/  proc_free (struct proc_handle*) ; 
 int proc_init (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_handle**) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int
proc_create(const char *file, char * const *argv, char * const *envp,
    proc_child_func *pcf, void *child_arg, struct proc_handle **pphdl)
{
	struct proc_handle *phdl;
	int error, status;
	pid_t pid;

	if (elf_version(EV_CURRENT) == EV_NONE)
		return (ENOENT);

	error = 0;
	phdl = NULL;

	if ((pid = fork()) == -1)
		error = errno;
	else if (pid == 0) {
		/* The child expects to be traced. */
		if (ptrace(PT_TRACE_ME, 0, 0, 0) != 0)
			_exit(1);

		if (pcf != NULL)
			(*pcf)(child_arg);

		if (envp != NULL)
			environ = envp;

		execvp(file, argv);

		_exit(2);
		/* NOTREACHED */
	} else {
		/* Wait for the child process to stop. */
		if (waitpid(pid, &status, WUNTRACED) == -1) {
			error = errno;
			DPRINTF("ERROR: child process %d didn't stop as expected", pid);
			goto bad;
		}

		/* Check for an unexpected status. */
		if (!WIFSTOPPED(status)) {
			error = ENOENT;
			DPRINTFX("ERROR: child process %d status 0x%x", pid, status);
			goto bad;
		}

		/* The parent owns the process handle. */
		error = proc_init(pid, 0, PS_IDLE, &phdl);
		if (error == 0)
			phdl->status = PS_STOP;

bad:
		if (error != 0 && phdl != NULL) {
			proc_free(phdl);
			phdl = NULL;
		}
	}
	*pphdl = phdl;
	return (error);
}