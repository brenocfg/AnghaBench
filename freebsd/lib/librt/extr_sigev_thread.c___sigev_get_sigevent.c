#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* sival_ptr; } ;
struct sigevent {TYPE_2__ sigev_value; scalar_t__ sigev_notify_thread_id; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct sigev_node {TYPE_1__* sn_tn; } ;
typedef  scalar_t__ sigev_id_t ;
typedef  scalar_t__ lwpid_t ;
struct TYPE_3__ {scalar_t__ tn_lwpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGEV_THREAD_ID ; 
 int /*<<< orphan*/  SIGLIBRT ; 

void
__sigev_get_sigevent(struct sigev_node *sn, struct sigevent *newevp,
	sigev_id_t id)
{
	/*
	 * Build a new sigevent, and tell kernel to deliver SIGLIBRT
	 * signal to the new thread.
	 */
	newevp->sigev_notify = SIGEV_THREAD_ID;
	newevp->sigev_signo  = SIGLIBRT;
	newevp->sigev_notify_thread_id = (lwpid_t)sn->sn_tn->tn_lwpid;
	newevp->sigev_value.sival_ptr = (void *)id;
}