#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* t_procp; } ;
struct TYPE_9__ {TYPE_3__* cr_zone; } ;
struct TYPE_8__ {scalar_t__ zone_dtrace_getf; } ;
struct TYPE_7__ {TYPE_1__* p_zone; } ;
struct TYPE_6__ {scalar_t__ zone_dtrace_getf; } ;

/* Variables and functions */
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 TYPE_4__* kcred ; 

__attribute__((used)) static void
dtrace_getf_barrier()
{
#ifdef illumos
	/*
	 * When we have unprivileged (that is, non-DTRACE_CRV_KERNEL) enablings
	 * that contain calls to getf(), this routine will be called on every
	 * closef() before either the underlying vnode is released or the
	 * file_t itself is freed.  By the time we are here, it is essential
	 * that the file_t can no longer be accessed from a call to getf()
	 * in probe context -- that assures that a dtrace_sync() can be used
	 * to clear out any enablings referring to the old structures.
	 */
	if (curthread->t_procp->p_zone->zone_dtrace_getf != 0 ||
	    kcred->cr_zone->zone_dtrace_getf != 0)
		dtrace_sync();
#endif
}