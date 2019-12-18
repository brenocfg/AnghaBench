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
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct kqueue {TYPE_2__ kq_sel; } ;
struct knote {scalar_t__ kn_filter; int /*<<< orphan*/ * kn_fop; int /*<<< orphan*/  kn_status; TYPE_1__* kn_fp; } ;
struct file {int dummy; } ;
struct TYPE_3__ {struct kqueue* f_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EVFILT_READ ; 
 int /*<<< orphan*/  KN_KQUEUE ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqread_filtops ; 

__attribute__((used)) static int
kqueue_kqfilter(struct file *fp, struct knote *kn)
{
	struct kqueue *kq = kn->kn_fp->f_data;

	if (kn->kn_filter != EVFILT_READ)
		return (EINVAL);

	kn->kn_status |= KN_KQUEUE;
	kn->kn_fop = &kqread_filtops;
	knlist_add(&kq->kq_sel.si_note, kn, 0);

	return (0);
}