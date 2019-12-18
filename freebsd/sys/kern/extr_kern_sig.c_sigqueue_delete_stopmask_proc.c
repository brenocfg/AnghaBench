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
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGEMPTYSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 int /*<<< orphan*/  sigqueue_delete_set_proc (struct proc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sigqueue_delete_stopmask_proc(struct proc *p)
{
	sigset_t set;

	SIGEMPTYSET(set);
	SIGADDSET(set, SIGSTOP);
	SIGADDSET(set, SIGTSTP);
	SIGADDSET(set, SIGTTIN);
	SIGADDSET(set, SIGTTOU);
	sigqueue_delete_set_proc(p, &set);
}