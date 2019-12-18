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
struct kldunloadf_args {scalar_t__ flags; int /*<<< orphan*/  fileid; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ LINKER_UNLOAD_FORCE ; 
 scalar_t__ LINKER_UNLOAD_NORMAL ; 
 int kern_kldunload (struct thread*,int /*<<< orphan*/ ,scalar_t__) ; 

int
sys_kldunloadf(struct thread *td, struct kldunloadf_args *uap)
{

	if (uap->flags != LINKER_UNLOAD_NORMAL &&
	    uap->flags != LINKER_UNLOAD_FORCE)
		return (EINVAL);
	return (kern_kldunload(td, uap->fileid, uap->flags));
}