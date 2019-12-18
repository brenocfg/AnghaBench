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
struct thread {uintptr_t* td_retval; } ;
struct break_args {scalar_t__ nsize; } ;

/* Variables and functions */
 int ENOSYS ; 
 int kern_break (struct thread*,uintptr_t*) ; 

int
sys_break(struct thread *td, struct break_args *uap)
{
#if !defined(__aarch64__) && !defined(__riscv)
	uintptr_t addr;
	int error;

	addr = (uintptr_t)uap->nsize;
	error = kern_break(td, &addr);
	if (error == 0)
		td->td_retval[0] = addr;
	return (error);
#else /* defined(__aarch64__) || defined(__riscv) */
	return (ENOSYS);
#endif /* defined(__aarch64__) || defined(__riscv) */
}