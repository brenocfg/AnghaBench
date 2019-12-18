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
struct knote {scalar_t__ kn_filter; int /*<<< orphan*/ * kn_fop; } ;
struct cdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {TYPE_1__ sel; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ EVFILT_READ ; 
 int /*<<< orphan*/  devctl_rfiltops ; 
 TYPE_2__ devsoftc ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devkqfilter(struct cdev *dev, struct knote *kn)
{
	int error;

	if (kn->kn_filter == EVFILT_READ) {
		kn->kn_fop = &devctl_rfiltops;
		knlist_add(&devsoftc.sel.si_note, kn, 0);
		error = 0;
	} else
		error = EINVAL;
	return (error);
}