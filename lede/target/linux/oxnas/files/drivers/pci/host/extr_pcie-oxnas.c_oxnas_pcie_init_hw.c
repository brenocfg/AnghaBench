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
typedef  scalar_t__ u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct oxnas_pcie {scalar_t__ card_reset; int /*<<< orphan*/  pcie_ctrl_offset; int /*<<< orphan*/  sys_ctrl; scalar_t__ haslink; scalar_t__ base; int /*<<< orphan*/  clk; int /*<<< orphan*/  hcsl_en; int /*<<< orphan*/  busclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_DEVICE_TYPE_MASK ; 
 int /*<<< orphan*/  PCIE_DEVICE_TYPE_ROOT ; 
 int /*<<< orphan*/  PCIE_LTSSM ; 
 int /*<<< orphan*/  PCIE_READY_ENTR_L23 ; 
 scalar_t__ PCI_CONFIG_VERSION_DEVICEID ; 
 int /*<<< orphan*/  SYS_CTRL_HCSL_CTRL_REGOFFSET ; 
 scalar_t__ VERSION_ID_MAGIC ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int device_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_direction_input (scalar_t__) ; 
 int /*<<< orphan*/  gpio_direction_output (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void oxnas_pcie_init_hw(struct platform_device *pdev,
			       struct oxnas_pcie *pcie)
{
	u32 version_id;
	int ret;

	clk_prepare_enable(pcie->busclk);

	/* reset PCIe cards use hard-wired gpio pin */
	if (pcie->card_reset >= 0 &&
	    !gpio_direction_output(pcie->card_reset, 0)) {
		wmb();
		mdelay(10);
		/* must tri-state the pin to pull it up */
		gpio_direction_input(pcie->card_reset);
		wmb();
		mdelay(100);
	}

	/* ToDo: use phy power-on port... */
	regmap_update_bits(pcie->sys_ctrl, SYS_CTRL_HCSL_CTRL_REGOFFSET,
	                   BIT(pcie->hcsl_en), BIT(pcie->hcsl_en));

	/* core */
	ret = device_reset(&pdev->dev);
	if (ret) {
		dev_err(&pdev->dev, "core reset failed %d\n", ret);
		return;
	}

	/* Start PCIe core clocks */
	clk_prepare_enable(pcie->clk);

	version_id = readl_relaxed(pcie->base + PCI_CONFIG_VERSION_DEVICEID);
	dev_info(&pdev->dev, "PCIe version/deviceID 0x%x\n", version_id);

	if (version_id != VERSION_ID_MAGIC) {
		dev_info(&pdev->dev, "PCIe controller not found\n");
		pcie->haslink = 0;
		return;
	}

	/* allow entry to L23 state */
	regmap_write_bits(pcie->sys_ctrl, pcie->pcie_ctrl_offset,
	                  PCIE_READY_ENTR_L23, PCIE_READY_ENTR_L23);

	/* Set PCIe core into RootCore mode */
	regmap_write_bits(pcie->sys_ctrl, pcie->pcie_ctrl_offset,
	                  PCIE_DEVICE_TYPE_MASK, PCIE_DEVICE_TYPE_ROOT);
	wmb();

	/* Bring up the PCI core */
	regmap_write_bits(pcie->sys_ctrl, pcie->pcie_ctrl_offset,
	                  PCIE_LTSSM, PCIE_LTSSM);
	wmb();
}