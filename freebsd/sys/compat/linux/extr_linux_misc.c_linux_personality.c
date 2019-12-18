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
typedef  int uint32_t ;
struct thread {int* td_retval; struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct linux_personality_args {int per; } ;
struct linux_pemuldata {int persona; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct linux_pemuldata* pem_find (struct proc*) ; 

int
linux_personality(struct thread *td, struct linux_personality_args *args)
{
	struct linux_pemuldata *pem;
	struct proc *p = td->td_proc;
	uint32_t old;

	PROC_LOCK(p);
	pem = pem_find(p);
	old = pem->persona;
	if (args->per != 0xffffffff)
		pem->persona = args->per;
	PROC_UNLOCK(p);

	td->td_retval[0] = old;
	return (0);
}