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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iosf_mbi_pmic_access_mutex ; 
 int /*<<< orphan*/  iosf_mbi_pmic_access_waitq ; 
 scalar_t__ iosf_mbi_pmic_i2c_access_count ; 
 int /*<<< orphan*/  iosf_mbi_reset_semaphore () ; 
 scalar_t__ iosf_mbi_sem_acquired ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 TYPE_1__* mbi_pdev ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iosf_mbi_unblock_punit_i2c_access(void)
{
	bool do_wakeup = false;

	mutex_lock(&iosf_mbi_pmic_access_mutex);
	iosf_mbi_pmic_i2c_access_count--;
	if (iosf_mbi_pmic_i2c_access_count == 0) {
		iosf_mbi_reset_semaphore();
		dev_dbg(&mbi_pdev->dev, "punit semaphore held for %ums\n",
			jiffies_to_msecs(jiffies - iosf_mbi_sem_acquired));
		do_wakeup = true;
	}
	mutex_unlock(&iosf_mbi_pmic_access_mutex);

	if (do_wakeup)
		wake_up(&iosf_mbi_pmic_access_waitq);
}