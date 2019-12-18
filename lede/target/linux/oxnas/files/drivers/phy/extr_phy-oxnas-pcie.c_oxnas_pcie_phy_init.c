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
struct reset_control {int dummy; } ;
struct phy {int dummy; } ;
struct oxnas_pcie_phy {int /*<<< orphan*/  dev; int /*<<< orphan*/  sys_ctrl; } ;

/* Variables and functions */
 int HCSL_BIAS_ON ; 
 int HCSL_PCIE_EN ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  SYS_CTRL_HCSL_CTRL_REGOFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct oxnas_pcie_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct reset_control* reset_control_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_control_put (struct reset_control*) ; 
 int reset_control_reset (struct reset_control*) ; 

__attribute__((used)) static int oxnas_pcie_phy_init(struct phy *phy)
{
	struct oxnas_pcie_phy *pciephy = phy_get_drvdata(phy);
	struct reset_control *rstc;
	int ret;

	/* generate clocks from HCSL buffers, shared parts */
	regmap_write(pciephy->sys_ctrl, SYS_CTRL_HCSL_CTRL_REGOFFSET, HCSL_BIAS_ON|HCSL_PCIE_EN);

	/* Ensure PCIe PHY is properly reset */
	rstc = reset_control_get(pciephy->dev, "phy");
	if (IS_ERR(rstc)) {
		ret = PTR_ERR(rstc);
	} else {
		ret = reset_control_reset(rstc);
		reset_control_put(rstc);
	}

	if (ret) {
		dev_err(pciephy->dev, "phy reset failed %d\n", ret);
		return ret;
	}

	return 0;
}