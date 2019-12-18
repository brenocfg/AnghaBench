#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct hpt_iop_hba {int /*<<< orphan*/  flag; } ;
typedef  int /*<<< orphan*/  ioctl_thread_t ;
typedef  int /*<<< orphan*/  ioctl_dev_t ;

/* Variables and functions */
 scalar_t__ HPT_IOCTL_FLAG_OPEN ; 
 struct hpt_iop_hba* hba_from_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hptiop_close(ioctl_dev_t dev, int flags,
					int devtype, ioctl_thread_t proc)
{
	struct hpt_iop_hba *hba = hba_from_dev(dev);
	hba->flag &= ~(u_int32_t)HPT_IOCTL_FLAG_OPEN;
	return 0;
}