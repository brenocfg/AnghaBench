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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct fpga_manager {int dummy; } ;
struct altera_cvp_conf {int vsec_offset; scalar_t__ map; int /*<<< orphan*/  mgr_name; int /*<<< orphan*/  write_data; int /*<<< orphan*/ * priv; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 char* ALTERA_CVP_MGR_NAME ; 
 int /*<<< orphan*/  CVP_BAR ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PCI_COMMAND ; 
 scalar_t__ PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_VNDR ; 
 int V1_VSEC_OFFSET ; 
 scalar_t__ VSE_CVP_STATUS ; 
 int VSE_CVP_STATUS_CVP_EN ; 
 scalar_t__ VSE_PCIE_EXT_CAP_ID ; 
 scalar_t__ VSE_PCIE_EXT_CAP_ID_VAL ; 
 int /*<<< orphan*/  altera_cvp_ops ; 
 int /*<<< orphan*/  altera_cvp_write_data_config ; 
 int /*<<< orphan*/  altera_cvp_write_data_iomem ; 
 int /*<<< orphan*/  cvp_priv_v1 ; 
 int /*<<< orphan*/  cvp_priv_v2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct fpga_manager* devm_fpga_mgr_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct altera_cvp_conf*) ; 
 struct altera_cvp_conf* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 int pci_find_next_ext_capability (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,scalar_t__) ; 
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fpga_manager*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 

__attribute__((used)) static int altera_cvp_probe(struct pci_dev *pdev,
			    const struct pci_device_id *dev_id)
{
	struct altera_cvp_conf *conf;
	struct fpga_manager *mgr;
	int ret, offset;
	u16 cmd, val;
	u32 regval;

	/* Discover the Vendor Specific Offset for this device */
	offset = pci_find_next_ext_capability(pdev, 0, PCI_EXT_CAP_ID_VNDR);
	if (!offset) {
		dev_err(&pdev->dev, "No Vendor Specific Offset.\n");
		return -ENODEV;
	}

	/*
	 * First check if this is the expected FPGA device. PCI config
	 * space access works without enabling the PCI device, memory
	 * space access is enabled further down.
	 */
	pci_read_config_word(pdev, offset + VSE_PCIE_EXT_CAP_ID, &val);
	if (val != VSE_PCIE_EXT_CAP_ID_VAL) {
		dev_err(&pdev->dev, "Wrong EXT_CAP_ID value 0x%x\n", val);
		return -ENODEV;
	}

	pci_read_config_dword(pdev, offset + VSE_CVP_STATUS, &regval);
	if (!(regval & VSE_CVP_STATUS_CVP_EN)) {
		dev_err(&pdev->dev,
			"CVP is disabled for this device: CVP_STATUS Reg 0x%x\n",
			regval);
		return -ENODEV;
	}

	conf = devm_kzalloc(&pdev->dev, sizeof(*conf), GFP_KERNEL);
	if (!conf)
		return -ENOMEM;

	conf->vsec_offset = offset;

	/*
	 * Enable memory BAR access. We cannot use pci_enable_device() here
	 * because it will make the driver unusable with FPGA devices that
	 * have additional big IOMEM resources (e.g. 4GiB BARs) on 32-bit
	 * platform. Such BARs will not have an assigned address range and
	 * pci_enable_device() will fail, complaining about not claimed BAR,
	 * even if the concerned BAR is not needed for FPGA configuration
	 * at all. Thus, enable the device via PCI config space command.
	 */
	pci_read_config_word(pdev, PCI_COMMAND, &cmd);
	if (!(cmd & PCI_COMMAND_MEMORY)) {
		cmd |= PCI_COMMAND_MEMORY;
		pci_write_config_word(pdev, PCI_COMMAND, cmd);
	}

	ret = pci_request_region(pdev, CVP_BAR, "CVP");
	if (ret) {
		dev_err(&pdev->dev, "Requesting CVP BAR region failed\n");
		goto err_disable;
	}

	conf->pci_dev = pdev;
	conf->write_data = altera_cvp_write_data_iomem;

	if (conf->vsec_offset == V1_VSEC_OFFSET)
		conf->priv = &cvp_priv_v1;
	else
		conf->priv = &cvp_priv_v2;

	conf->map = pci_iomap(pdev, CVP_BAR, 0);
	if (!conf->map) {
		dev_warn(&pdev->dev, "Mapping CVP BAR failed\n");
		conf->write_data = altera_cvp_write_data_config;
	}

	snprintf(conf->mgr_name, sizeof(conf->mgr_name), "%s @%s",
		 ALTERA_CVP_MGR_NAME, pci_name(pdev));

	mgr = devm_fpga_mgr_create(&pdev->dev, conf->mgr_name,
				   &altera_cvp_ops, conf);
	if (!mgr) {
		ret = -ENOMEM;
		goto err_unmap;
	}

	pci_set_drvdata(pdev, mgr);

	ret = fpga_mgr_register(mgr);
	if (ret)
		goto err_unmap;

	return 0;

err_unmap:
	if (conf->map)
		pci_iounmap(pdev, conf->map);
	pci_release_region(pdev, CVP_BAR);
err_disable:
	cmd &= ~PCI_COMMAND_MEMORY;
	pci_write_config_word(pdev, PCI_COMMAND, cmd);
	return ret;
}