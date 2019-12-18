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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MBI_PMIC_BUS_ACCESS_BEGIN ; 
 int /*<<< orphan*/  MBI_REG_WRITE ; 
 int /*<<< orphan*/  PUNIT_SEMAPHORE_ACQUIRE ; 
 int /*<<< orphan*/  SEMAPHORE_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int iosf_mbi_get_sem (scalar_t__*) ; 
 int /*<<< orphan*/  iosf_mbi_pm_qos ; 
 int /*<<< orphan*/  iosf_mbi_pmic_access_mutex ; 
 int /*<<< orphan*/  iosf_mbi_pmic_access_waitq ; 
 int /*<<< orphan*/  iosf_mbi_pmic_bus_access_notifier ; 
 scalar_t__ iosf_mbi_pmic_i2c_access_count ; 
 scalar_t__ iosf_mbi_pmic_punit_access_count ; 
 int /*<<< orphan*/  iosf_mbi_reset_semaphore () ; 
 unsigned long iosf_mbi_sem_acquired ; 
 int /*<<< orphan*/  iosf_mbi_sem_address ; 
 int iosf_mbi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 TYPE_1__* mbi_pdev ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int iosf_mbi_block_punit_i2c_access(void)
{
	unsigned long start, end;
	int ret = 0;
	u32 sem;

	if (WARN_ON(!mbi_pdev || !iosf_mbi_sem_address))
		return -ENXIO;

	mutex_lock(&iosf_mbi_pmic_access_mutex);

	while (iosf_mbi_pmic_punit_access_count != 0) {
		mutex_unlock(&iosf_mbi_pmic_access_mutex);
		wait_event(iosf_mbi_pmic_access_waitq,
			   iosf_mbi_pmic_punit_access_count == 0);
		mutex_lock(&iosf_mbi_pmic_access_mutex);
	}

	if (iosf_mbi_pmic_i2c_access_count > 0)
		goto success;

	blocking_notifier_call_chain(&iosf_mbi_pmic_bus_access_notifier,
				     MBI_PMIC_BUS_ACCESS_BEGIN, NULL);

	/*
	 * Disallow the CPU to enter C6 or C7 state, entering these states
	 * requires the P-Unit to talk to the PMIC and if this happens while
	 * we're holding the semaphore, the SoC hangs.
	 */
	pm_qos_update_request(&iosf_mbi_pm_qos, 0);

	/* host driver writes to side band semaphore register */
	ret = iosf_mbi_write(BT_MBI_UNIT_PMC, MBI_REG_WRITE,
			     iosf_mbi_sem_address, PUNIT_SEMAPHORE_ACQUIRE);
	if (ret) {
		dev_err(&mbi_pdev->dev, "Error P-Unit semaphore request failed\n");
		goto error;
	}

	/* host driver waits for bit 0 to be set in semaphore register */
	start = jiffies;
	end = start + msecs_to_jiffies(SEMAPHORE_TIMEOUT);
	do {
		ret = iosf_mbi_get_sem(&sem);
		if (!ret && sem) {
			iosf_mbi_sem_acquired = jiffies;
			dev_dbg(&mbi_pdev->dev, "P-Unit semaphore acquired after %ums\n",
				jiffies_to_msecs(jiffies - start));
			goto success;
		}

		usleep_range(1000, 2000);
	} while (time_before(jiffies, end));

	ret = -ETIMEDOUT;
	dev_err(&mbi_pdev->dev, "Error P-Unit semaphore timed out, resetting\n");
error:
	iosf_mbi_reset_semaphore();
	if (!iosf_mbi_get_sem(&sem))
		dev_err(&mbi_pdev->dev, "P-Unit semaphore: %d\n", sem);
success:
	if (!WARN_ON(ret))
		iosf_mbi_pmic_i2c_access_count++;

	mutex_unlock(&iosf_mbi_pmic_access_mutex);

	return ret;
}