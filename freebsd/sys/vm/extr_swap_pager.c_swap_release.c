#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_ooffset_t ;
struct ucred {int dummy; } ;
struct TYPE_4__ {struct ucred* p_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_1__*) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  swap_release_by_cred (int /*<<< orphan*/ ,struct ucred*) ; 

void
swap_release(vm_ooffset_t decr)
{
	struct ucred *cred;

	PROC_LOCK(curproc);
	cred = curproc->p_ucred;
	swap_release_by_cred(decr, cred);
	PROC_UNLOCK(curproc);
}