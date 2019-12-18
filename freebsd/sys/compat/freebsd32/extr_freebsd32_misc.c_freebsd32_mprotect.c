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
struct thread {int dummy; } ;
struct freebsd32_mprotect_args {int prot; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int PROT_EXEC ; 
 int PROT_READ ; 
 scalar_t__ PTRIN (int /*<<< orphan*/ ) ; 
 scalar_t__ i386_read_exec ; 
 int kern_mprotect (struct thread*,uintptr_t,int /*<<< orphan*/ ,int) ; 

int
freebsd32_mprotect(struct thread *td, struct freebsd32_mprotect_args *uap)
{
	int prot;

	prot = uap->prot;
#if defined(__amd64__)
	if (i386_read_exec && (prot & PROT_READ) != 0)
		prot |= PROT_EXEC;
#endif
	return (kern_mprotect(td, (uintptr_t)PTRIN(uap->addr), uap->len,
	    prot));
}