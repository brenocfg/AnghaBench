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
struct hpt_iop_hba {int flag; } ;
typedef  int /*<<< orphan*/  ioctl_thread_t ;
typedef  int /*<<< orphan*/  ioctl_dev_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int HPT_IOCTL_FLAG_OPEN ; 
 struct hpt_iop_hba* hba_from_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hptiop_open(ioctl_dev_t dev, int flags,
					int devtype, ioctl_thread_t proc)
{
	struct hpt_iop_hba *hba = hba_from_dev(dev);

	if (hba==NULL)
		return ENXIO;
	if (hba->flag & HPT_IOCTL_FLAG_OPEN)
		return EBUSY;
	hba->flag |= HPT_IOCTL_FLAG_OPEN;
	return 0;
}