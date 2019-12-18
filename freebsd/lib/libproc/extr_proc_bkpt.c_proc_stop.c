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

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFX (char*,int) ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WSTOPPED ; 
 int kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proc_stop(struct proc_handle *phdl)
{
	int status;

	if (kill(proc_getpid(phdl), SIGSTOP) == -1) {
		DPRINTF("kill %d", proc_getpid(phdl));
		return (-1);
	} else if (waitpid(proc_getpid(phdl), &status, WSTOPPED) == -1) {
		DPRINTF("waitpid %d", proc_getpid(phdl));
		return (-1);
	} else if (!WIFSTOPPED(status)) {
		DPRINTFX("waitpid: unexpected status 0x%x", status);
		return (-1);
	}

	return (0);
}