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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct timerfd {TYPE_1__ tfd_sel; } ;
struct knote {scalar_t__ kn_filter; struct timerfd* kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct file {scalar_t__ f_type; struct timerfd* f_data; } ;

/* Variables and functions */
 scalar_t__ DTYPE_LINUXTFD ; 
 int EINVAL ; 
 scalar_t__ EVFILT_READ ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timerfd_rfiltops ; 

__attribute__((used)) static int
timerfd_kqfilter(struct file *fp, struct knote *kn)
{
	struct timerfd *tfd;

	tfd = fp->f_data;
	if (fp->f_type != DTYPE_LINUXTFD || tfd == NULL)
		return (EINVAL);

	if (kn->kn_filter == EVFILT_READ)
		kn->kn_fop = &timerfd_rfiltops;
	else
		return (EINVAL);

	kn->kn_hook = tfd;
	knlist_add(&tfd->tfd_sel.si_note, kn, 0);

	return (0);
}