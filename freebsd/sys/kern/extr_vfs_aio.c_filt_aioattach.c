#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct kaiocb* p_aio; } ;
struct knote {int kn_flags; TYPE_1__ kn_ptr; scalar_t__ kn_sdata; } ;
struct kaiocb {int /*<<< orphan*/  klist; } ;

/* Variables and functions */
 int EPERM ; 
 int EV_FLAG1 ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_aioattach(struct knote *kn)
{
	struct kaiocb *job;

	job = (struct kaiocb *)(uintptr_t)kn->kn_sdata;

	/*
	 * The job pointer must be validated before using it, so
	 * registration is restricted to the kernel; the user cannot
	 * set EV_FLAG1.
	 */
	if ((kn->kn_flags & EV_FLAG1) == 0)
		return (EPERM);
	kn->kn_ptr.p_aio = job;
	kn->kn_flags &= ~EV_FLAG1;

	knlist_add(&job->klist, kn, 0);

	return (0);
}