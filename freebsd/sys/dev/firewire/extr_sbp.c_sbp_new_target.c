#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  w ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct sbp_softc {TYPE_4__* targets; TYPE_2__ fd; } ;
struct TYPE_8__ {scalar_t__ lo; int /*<<< orphan*/  hi; } ;
struct fw_device {TYPE_3__ eui; } ;
struct TYPE_6__ {scalar_t__ lo; int /*<<< orphan*/  hi; } ;
struct TYPE_10__ {int bus; size_t target; TYPE_1__ eui; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fwdev; } ;

/* Variables and functions */
 int SBP_NUM_TARGETS ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* wired ; 

__attribute__((used)) static int
sbp_new_target(struct sbp_softc *sbp, struct fw_device *fwdev)
{
	int bus, i, target=-1;
	char w[SBP_NUM_TARGETS];

	bzero(w, sizeof(w));
	bus = device_get_unit(sbp->fd.dev);

	/* XXX wired-down configuration should be gotten from
					tunable or device hint */
	for (i = 0; wired[i].bus >= 0; i++) {
		if (wired[i].bus == bus) {
			w[wired[i].target] = 1;
			if (wired[i].eui.hi == fwdev->eui.hi &&
					wired[i].eui.lo == fwdev->eui.lo)
				target = wired[i].target;
		}
	}
	if (target >= 0) {
		if (target < SBP_NUM_TARGETS &&
				sbp->targets[target].fwdev == NULL)
			return (target);
		device_printf(sbp->fd.dev,
			"target %d is not free for %08x:%08x\n",
			target, fwdev->eui.hi, fwdev->eui.lo);
		target = -1;
	}
	/* non-wired target */
	for (i = 0; i < SBP_NUM_TARGETS; i++)
		if (sbp->targets[i].fwdev == NULL && w[i] == 0) {
			target = i;
			break;
		}

	return target;
}