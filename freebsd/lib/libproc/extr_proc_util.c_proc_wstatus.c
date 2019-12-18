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
struct proc_handle {int status; int wstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ EINTR ; 
 int PS_STOP ; 
 int PS_UNDEAD ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int /*<<< orphan*/  WUNTRACED ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 scalar_t__ waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
proc_wstatus(struct proc_handle *phdl)
{
	int status;

	if (phdl == NULL)
		return (-1);
	if (waitpid(proc_getpid(phdl), &status, WUNTRACED) < 0) {
		if (errno != EINTR)
			DPRINTF("waitpid");
		return (-1);
	}
	if (WIFSTOPPED(status))
		phdl->status = PS_STOP;
	if (WIFEXITED(status) || WIFSIGNALED(status))
		phdl->status = PS_UNDEAD;
	phdl->wstat = status;

	return (phdl->status);
}