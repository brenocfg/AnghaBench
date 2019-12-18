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
struct proc_handle {scalar_t__ status; int /*<<< orphan*/  wstat; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ PS_RUN ; 
 scalar_t__ PS_STOP ; 
 int /*<<< orphan*/  PT_CONTINUE ; 
 int SIGTRAP ; 
 int WSTOPSIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_getpid (struct proc_handle*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
proc_continue(struct proc_handle *phdl)
{
	int pending;

	if (phdl == NULL)
		return (-1);

	if (phdl->status == PS_STOP && WSTOPSIG(phdl->wstat) != SIGTRAP)
		pending = WSTOPSIG(phdl->wstat);
	else
		pending = 0;
	if (ptrace(PT_CONTINUE, proc_getpid(phdl), (caddr_t)(uintptr_t)1,
	    pending) != 0)
		return (-1);

	phdl->status = PS_RUN;

	return (0);
}