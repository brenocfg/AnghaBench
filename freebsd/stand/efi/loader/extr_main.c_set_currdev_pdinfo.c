#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  d_unit; TYPE_5__* d_dev; } ;
struct disk_devdesc {int /*<<< orphan*/  d_partition; int /*<<< orphan*/  d_slice; TYPE_1__ dd; } ;
struct devdesc {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  pd_unit; TYPE_5__* pd_devsw; TYPE_2__* pd_parent; } ;
typedef  TYPE_3__ pdinfo_t ;
struct TYPE_9__ {scalar_t__ dv_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  pd_unit; } ;

/* Variables and functions */
 scalar_t__ DEVT_DISK ; 
 int /*<<< orphan*/  D_PARTISGPT ; 
 int /*<<< orphan*/  D_PARTNONE ; 
 int /*<<< orphan*/  D_SLICENONE ; 
 int /*<<< orphan*/  set_currdev_devdesc (struct devdesc*) ; 
 int /*<<< orphan*/  set_currdev_devsw (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_currdev_pdinfo(pdinfo_t *dp)
{

	/*
	 * Disks are special: they have partitions. if the parent
	 * pointer is non-null, we're a partition not a full disk
	 * and we need to adjust currdev appropriately.
	 */
	if (dp->pd_devsw->dv_type == DEVT_DISK) {
		struct disk_devdesc currdev;

		currdev.dd.d_dev = dp->pd_devsw;
		if (dp->pd_parent == NULL) {
			currdev.dd.d_unit = dp->pd_unit;
			currdev.d_slice = D_SLICENONE;
			currdev.d_partition = D_PARTNONE;
		} else {
			currdev.dd.d_unit = dp->pd_parent->pd_unit;
			currdev.d_slice = dp->pd_unit;
			currdev.d_partition = D_PARTISGPT; /* XXX Assumes GPT */
		}
		set_currdev_devdesc((struct devdesc *)&currdev);
	} else {
		set_currdev_devsw(dp->pd_devsw, dp->pd_unit);
	}
}