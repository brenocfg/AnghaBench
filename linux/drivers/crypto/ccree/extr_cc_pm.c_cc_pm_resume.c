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
struct device {int dummy; } ;
struct cc_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  HOST_POWER_DOWN_EN ; 
 int /*<<< orphan*/  POWER_DOWN_DISABLE ; 
 int cc_clk_on (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_init_hash_sram (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cc_resume_req_queue (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_tee_handle_fips_error (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_wait_for_reset_completion (struct cc_drvdata*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct cc_drvdata* dev_get_drvdata (struct device*) ; 
 int init_cc_regs (struct cc_drvdata*,int) ; 

int cc_pm_resume(struct device *dev)
{
	int rc;
	struct cc_drvdata *drvdata = dev_get_drvdata(dev);

	dev_dbg(dev, "unset HOST_POWER_DOWN_EN\n");
	/* Enables the device source clk */
	rc = cc_clk_on(drvdata);
	if (rc) {
		dev_err(dev, "failed getting clock back on. We're toast.\n");
		return rc;
	}
	/* wait for Crytpcell reset completion */
	if (!cc_wait_for_reset_completion(drvdata)) {
		dev_err(dev, "Cryptocell reset not completed");
		return -EBUSY;
	}

	cc_iowrite(drvdata, CC_REG(HOST_POWER_DOWN_EN), POWER_DOWN_DISABLE);
	rc = init_cc_regs(drvdata, false);
	if (rc) {
		dev_err(dev, "init_cc_regs (%x)\n", rc);
		return rc;
	}
	/* check if tee fips error occurred during power down */
	cc_tee_handle_fips_error(drvdata);

	rc = cc_resume_req_queue(drvdata);
	if (rc) {
		dev_err(dev, "cc_resume_req_queue (%x)\n", rc);
		return rc;
	}

	/* must be after the queue resuming as it uses the HW queue*/
	cc_init_hash_sram(drvdata);

	return 0;
}