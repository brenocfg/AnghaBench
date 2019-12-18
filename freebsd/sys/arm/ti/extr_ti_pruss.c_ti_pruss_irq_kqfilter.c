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
struct ti_pruss_irqsc {TYPE_1__ sc_selinfo; } ;
struct knote {int kn_filter; int /*<<< orphan*/ * kn_fop; struct ti_pruss_irqsc* kn_hook; } ;
struct cdev {struct ti_pruss_irqsc* si_drv1; } ;

/* Variables and functions */
 int EINVAL ; 
#define  EVFILT_READ 128 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pruss_kq_read ; 

__attribute__((used)) static int
ti_pruss_irq_kqfilter(struct cdev *cdev, struct knote *kn)
{
	struct ti_pruss_irqsc *sc = cdev->si_drv1;

	switch (kn->kn_filter) {
	case EVFILT_READ:
		kn->kn_hook = sc;
		kn->kn_fop = &ti_pruss_kq_read;
		knlist_add(&sc->sc_selinfo.si_note, kn, 0);
		break;
	default:
		return (EINVAL);
	}

	return (0);
}