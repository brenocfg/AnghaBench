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
struct linux_mremap_args {int flags; int addr; uintptr_t new_len; uintptr_t old_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int LINUX_MREMAP_FIXED ; 
 int LINUX_MREMAP_MAYMOVE ; 
 int PAGE_MASK ; 
 int kern_munmap (struct thread*,uintptr_t,size_t) ; 
 void* round_page (uintptr_t) ; 

int
linux_mremap(struct thread *td, struct linux_mremap_args *args)
{
	uintptr_t addr;
	size_t len;
	int error = 0;

	if (args->flags & ~(LINUX_MREMAP_FIXED | LINUX_MREMAP_MAYMOVE)) {
		td->td_retval[0] = 0;
		return (EINVAL);
	}

	/*
	 * Check for the page alignment.
	 * Linux defines PAGE_MASK to be FreeBSD ~PAGE_MASK.
	 */
	if (args->addr & PAGE_MASK) {
		td->td_retval[0] = 0;
		return (EINVAL);
	}

	args->new_len = round_page(args->new_len);
	args->old_len = round_page(args->old_len);

	if (args->new_len > args->old_len) {
		td->td_retval[0] = 0;
		return (ENOMEM);
	}

	if (args->new_len < args->old_len) {
		addr = args->addr + args->new_len;
		len = args->old_len - args->new_len;
		error = kern_munmap(td, addr, len);
	}

	td->td_retval[0] = error ? 0 : (uintptr_t)args->addr;
	return (error);
}