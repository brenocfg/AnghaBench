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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CPU_PM_ENTER 130 
#define  CPU_PM_ENTER_FAILED 129 
#define  CPU_PM_EXIT 128 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int notifier_from_errno (int) ; 
 int sdei_mask_local_cpu () ; 
 int sdei_unmask_local_cpu () ; 

__attribute__((used)) static int sdei_pm_notifier(struct notifier_block *nb, unsigned long action,
			    void *data)
{
	int rv;

	switch (action) {
	case CPU_PM_ENTER:
		rv = sdei_mask_local_cpu();
		break;
	case CPU_PM_EXIT:
	case CPU_PM_ENTER_FAILED:
		rv = sdei_unmask_local_cpu();
		break;
	default:
		return NOTIFY_DONE;
	}

	if (rv)
		return notifier_from_errno(rv);

	return NOTIFY_OK;
}