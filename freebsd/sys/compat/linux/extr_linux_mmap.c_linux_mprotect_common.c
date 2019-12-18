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

/* Variables and functions */
 int EINVAL ; 
 int LINUX_PROT_GROWSDOWN ; 
 int LINUX_PROT_GROWSUP ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int kern_mprotect (struct thread*,uintptr_t,size_t,int) ; 
 int /*<<< orphan*/  linux_fixup_prot (struct thread*,int*) ; 

int
linux_mprotect_common(struct thread *td, uintptr_t addr, size_t len, int prot)
{

	/* XXX Ignore PROT_GROWSDOWN and PROT_GROWSUP for now. */
	prot &= ~(LINUX_PROT_GROWSDOWN | LINUX_PROT_GROWSUP);
	if ((prot & ~(PROT_READ | PROT_WRITE | PROT_EXEC)) != 0)
		return (EINVAL);

#if defined(__amd64__)
	linux_fixup_prot(td, &prot);
#endif
	return (kern_mprotect(td, addr, len, prot));
}