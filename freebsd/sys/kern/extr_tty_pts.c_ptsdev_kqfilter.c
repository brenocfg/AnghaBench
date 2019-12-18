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
struct tty {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct pts_softc {TYPE_2__ pts_inpoll; TYPE_1__ pts_outpoll; } ;
struct knote {int kn_filter; int /*<<< orphan*/ * kn_fop; } ;
struct file {struct tty* f_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  pts_kqops_read ; 
 int /*<<< orphan*/  pts_kqops_write ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 struct pts_softc* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static int
ptsdev_kqfilter(struct file *fp, struct knote *kn)
{
	struct tty *tp = fp->f_data;
	struct pts_softc *psc = tty_softc(tp);
	int error = 0;

	tty_lock(tp);

	switch (kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_fop = &pts_kqops_read;
		knlist_add(&psc->pts_outpoll.si_note, kn, 1);
		break;
	case EVFILT_WRITE:
		kn->kn_fop = &pts_kqops_write;
		knlist_add(&psc->pts_inpoll.si_note, kn, 1);
		break;
	default:
		error = EINVAL;
		break;
	}

	tty_unlock(tp);
	return (error);
}