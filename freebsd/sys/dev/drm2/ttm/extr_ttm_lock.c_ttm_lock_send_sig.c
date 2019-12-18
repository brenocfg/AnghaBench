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

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  kern_psignal (struct proc*,int) ; 

__attribute__((used)) static void
ttm_lock_send_sig(int signo)
{
	struct proc *p;

	p = curproc;	/* XXXKIB curthread ? */
	PROC_LOCK(p);
	kern_psignal(p, signo);
	PROC_UNLOCK(p);
}