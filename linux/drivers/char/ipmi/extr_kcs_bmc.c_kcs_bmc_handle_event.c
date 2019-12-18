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
typedef  int u8 ;
struct kcs_bmc {int /*<<< orphan*/  lock; int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int ENODATA ; 
 int KCS_STATUS_CMD_DAT ; 
 int KCS_STATUS_IBF ; 
 int /*<<< orphan*/  kcs_bmc_handle_cmd (struct kcs_bmc*) ; 
 int /*<<< orphan*/  kcs_bmc_handle_data (struct kcs_bmc*) ; 
 int /*<<< orphan*/  kcs_force_abort (struct kcs_bmc*) ; 
 int read_status (struct kcs_bmc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int kcs_bmc_handle_event(struct kcs_bmc *kcs_bmc)
{
	unsigned long flags;
	int ret = -ENODATA;
	u8 status;

	spin_lock_irqsave(&kcs_bmc->lock, flags);

	status = read_status(kcs_bmc);
	if (status & KCS_STATUS_IBF) {
		if (!kcs_bmc->running)
			kcs_force_abort(kcs_bmc);
		else if (status & KCS_STATUS_CMD_DAT)
			kcs_bmc_handle_cmd(kcs_bmc);
		else
			kcs_bmc_handle_data(kcs_bmc);

		ret = 0;
	}

	spin_unlock_irqrestore(&kcs_bmc->lock, flags);

	return ret;
}