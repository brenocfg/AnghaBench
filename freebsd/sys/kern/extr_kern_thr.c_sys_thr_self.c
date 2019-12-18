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
struct thread {scalar_t__ td_tid; } ;
struct thr_self_args {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EFAULT ; 
 int suword_lwpid (int /*<<< orphan*/ ,unsigned int) ; 

int
sys_thr_self(struct thread *td, struct thr_self_args *uap)
    /* long *id */
{
	int error;

	error = suword_lwpid(uap->id, (unsigned)td->td_tid);
	if (error == -1)
		return (EFAULT);
	return (0);
}