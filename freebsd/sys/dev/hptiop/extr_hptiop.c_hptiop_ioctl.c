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
typedef  int u_long ;
struct hpt_iop_ioctl_param {int dummy; } ;
struct hpt_iop_hba {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  ioctl_thread_t ;
typedef  int /*<<< orphan*/  ioctl_dev_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int (* do_ioctl ) (struct hpt_iop_hba*,struct hpt_iop_ioctl_param*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  Giant ; 
#define  HPT_DO_IOCONTROL 129 
#define  HPT_SCAN_BUS 128 
 struct hpt_iop_hba* hba_from_dev (int /*<<< orphan*/ ) ; 
 int hptiop_rescan_bus (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct hpt_iop_hba*,struct hpt_iop_ioctl_param*) ; 

__attribute__((used)) static int hptiop_ioctl(ioctl_dev_t dev, u_long cmd, caddr_t data,
					int flags, ioctl_thread_t proc)
{
	int ret = EFAULT;
	struct hpt_iop_hba *hba = hba_from_dev(dev);

	mtx_lock(&Giant);

	switch (cmd) {
	case HPT_DO_IOCONTROL:
		ret = hba->ops->do_ioctl(hba,
				(struct hpt_iop_ioctl_param *)data);
		break;
	case HPT_SCAN_BUS:
		ret = hptiop_rescan_bus(hba);
		break;
	}

	mtx_unlock(&Giant);

	return ret;
}