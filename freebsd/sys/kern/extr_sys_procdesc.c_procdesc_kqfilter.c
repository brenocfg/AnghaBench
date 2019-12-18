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
struct procdesc {TYPE_1__ pd_selinfo; } ;
struct knote {int kn_filter; int /*<<< orphan*/  kn_flags; int /*<<< orphan*/ * kn_fop; } ;
struct file {struct procdesc* f_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EVFILT_PROCDESC 128 
 int /*<<< orphan*/  EV_CLEAR ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procdesc_kqops ; 

__attribute__((used)) static int
procdesc_kqfilter(struct file *fp, struct knote *kn)
{
	struct procdesc *pd;

	pd = fp->f_data;
	switch (kn->kn_filter) {
	case EVFILT_PROCDESC:
		kn->kn_fop = &procdesc_kqops;
		kn->kn_flags |= EV_CLEAR;
		knlist_add(&pd->pd_selinfo.si_note, kn, 0);
		return (0);
	default:
		return (EINVAL);
	}
}