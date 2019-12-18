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
struct knote {int kn_filter; struct eventfd* kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct file {scalar_t__ f_type; struct eventfd* f_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct eventfd {int /*<<< orphan*/  efd_lock; TYPE_1__ efd_sel; } ;

/* Variables and functions */
 scalar_t__ DTYPE_LINUXEFD ; 
 int EINVAL ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  eventfd_rfiltops ; 
 int /*<<< orphan*/  eventfd_wfiltops ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
eventfd_kqfilter(struct file *fp, struct knote *kn)
{
	struct eventfd *efd;

	efd = fp->f_data;
	if (fp->f_type != DTYPE_LINUXEFD || efd == NULL)
		return (EINVAL);

	mtx_lock(&efd->efd_lock);
	switch (kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &eventfd_rfiltops;
		break;
	case EVFILT_WRITE:
		kn->kn_fop = &eventfd_wfiltops;
		break;
	default:
		mtx_unlock(&efd->efd_lock);
		return (EINVAL);
	}

	kn->kn_hook = efd;
	knlist_add(&efd->efd_sel.si_note, kn, 1);
	mtx_unlock(&efd->efd_lock);

	return (0);
}