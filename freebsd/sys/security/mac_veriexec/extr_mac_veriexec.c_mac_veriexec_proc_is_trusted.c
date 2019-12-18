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
struct ucred {int dummy; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int PROC_LOCKED (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int VERIEXEC_TRUSTED ; 
 int mac_veriexec_metadata_get_executable_flags (struct ucred*,struct proc*,int*,int /*<<< orphan*/ ) ; 

int
mac_veriexec_proc_is_trusted(struct ucred *cred, struct proc *p)
{
	int already_locked, error, flags;

	/* Make sure we lock the process if we do not already have the lock */
	already_locked = PROC_LOCKED(p);
	if (!already_locked)
		PROC_LOCK(p);

	error = mac_veriexec_metadata_get_executable_flags(cred, p, &flags, 0);

	/* Unlock the process if we locked it previously */
	if (!already_locked)
		PROC_UNLOCK(p);

	/* Any errors, deny access */
	if (error != 0)
		return (0);

	/* Check that the trusted flag is set */
	return ((flags & VERIEXEC_TRUSTED) == VERIEXEC_TRUSTED);
}