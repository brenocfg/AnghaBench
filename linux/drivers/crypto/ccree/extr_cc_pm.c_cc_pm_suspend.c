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
 int /*<<< orphan*/  HOST_POWER_DOWN_EN ; 
 int /*<<< orphan*/  POWER_DOWN_ENABLE ; 
 int /*<<< orphan*/  cc_clk_off (struct cc_drvdata*) ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cc_suspend_req_queue (struct cc_drvdata*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct cc_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fini_cc_regs (struct cc_drvdata*) ; 

int cc_pm_suspend(struct device *dev)
{
	struct cc_drvdata *drvdata = dev_get_drvdata(dev);
	int rc;

	dev_dbg(dev, "set HOST_POWER_DOWN_EN\n");
	rc = cc_suspend_req_queue(drvdata);
	if (rc) {
		dev_err(dev, "cc_suspend_req_queue (%x)\n", rc);
		return rc;
	}
	fini_cc_regs(drvdata);
	cc_iowrite(drvdata, CC_REG(HOST_POWER_DOWN_EN), POWER_DOWN_ENABLE);
	cc_clk_off(drvdata);
	return 0;
}