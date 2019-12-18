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
struct cloudabi_sys_mem_sync_args {int flags; int /*<<< orphan*/  mapping_len; scalar_t__ mapping; } ;

/* Variables and functions */
#define  CLOUDABI_MS_ASYNC 129 
 int CLOUDABI_MS_INVALIDATE ; 
#define  CLOUDABI_MS_SYNC 128 
 int EINVAL ; 
 int MS_ASYNC ; 
 int MS_INVALIDATE ; 
 int MS_SYNC ; 
 int kern_msync (struct thread*,uintptr_t,int /*<<< orphan*/ ,int) ; 

int
cloudabi_sys_mem_sync(struct thread *td, struct cloudabi_sys_mem_sync_args *uap)
{
	int flags;

	/* Convert flags. */
	switch (uap->flags & (CLOUDABI_MS_ASYNC | CLOUDABI_MS_SYNC)) {
	case CLOUDABI_MS_ASYNC:
		flags = MS_ASYNC;
		break;
	case CLOUDABI_MS_SYNC:
		flags = MS_SYNC;
		break;
	default:
		return (EINVAL);
	}
	if ((uap->flags & CLOUDABI_MS_INVALIDATE) != 0)
		flags |= MS_INVALIDATE;

	return (kern_msync(td, (uintptr_t)uap->mapping, uap->mapping_len,
	    flags));
}