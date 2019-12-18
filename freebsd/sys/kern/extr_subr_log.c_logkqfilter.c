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
struct knote {scalar_t__ kn_filter; int /*<<< orphan*/ * kn_hook; int /*<<< orphan*/ * kn_fop; } ;
struct cdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {TYPE_1__ sc_selp; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EVFILT_READ ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int) ; 
 int /*<<< orphan*/  log_read_filterops ; 
 TYPE_2__ logsoftc ; 
 int /*<<< orphan*/  msgbuf_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
logkqfilter(struct cdev *dev, struct knote *kn)
{

	if (kn->kn_filter != EVFILT_READ)
		return (EINVAL);

	kn->kn_fop = &log_read_filterops;
	kn->kn_hook = NULL;

	mtx_lock(&msgbuf_lock);
	knlist_add(&logsoftc.sc_selp.si_note, kn, 1);
	mtx_unlock(&msgbuf_lock);
	return (0);
}