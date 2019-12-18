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
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct linux_set_tid_address_args {int /*<<< orphan*/  tidptr; } ;
struct linux_emuldata {int /*<<< orphan*/  em_tid; int /*<<< orphan*/  child_clear_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LINUX_CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct linux_emuldata* em_find (struct thread*) ; 
 int /*<<< orphan*/  set_tid_address ; 

int
linux_set_tid_address(struct thread *td, struct linux_set_tid_address_args *args)
{
	struct linux_emuldata *em;

	em = em_find(td);
	KASSERT(em != NULL, ("set_tid_address: emuldata not found.\n"));

	em->child_clear_tid = args->tidptr;

	td->td_retval[0] = em->em_tid;

	LINUX_CTR3(set_tid_address, "tidptr(%d) %p, returns %d",
	    em->em_tid, args->tidptr, td->td_retval[0]);

	return (0);
}