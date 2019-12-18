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
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct mqueue {TYPE_1__ mq_wsel; TYPE_2__ mq_rsel; } ;
struct knote {scalar_t__ kn_filter; int /*<<< orphan*/ * kn_fop; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EVFILT_READ ; 
 scalar_t__ EVFILT_WRITE ; 
 struct mqueue* FPTOMQ (struct file*) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mq_rfiltops ; 
 int /*<<< orphan*/  mq_wfiltops ; 

__attribute__((used)) static int
mqf_kqfilter(struct file *fp, struct knote *kn)
{
	struct mqueue *mq = FPTOMQ(fp);
	int error = 0;

	if (kn->kn_filter == EVFILT_READ) {
		kn->kn_fop = &mq_rfiltops;
		knlist_add(&mq->mq_rsel.si_note, kn, 0);
	} else if (kn->kn_filter == EVFILT_WRITE) {
		kn->kn_fop = &mq_wfiltops;
		knlist_add(&mq->mq_wsel.si_note, kn, 0);
	} else
		error = EINVAL;
	return (error);
}