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
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct cpt_device {int /*<<< orphan*/  reg_base; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpt_device_init (struct cpt_device*) ; 
 int cpt_register_interrupts (struct cpt_device*) ; 
 int cpt_sriov_init (struct cpt_device*,int) ; 
 int cpt_ucode_load (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_unregister_interrupts (struct cpt_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct cpt_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int num_vfs ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct cpt_device*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpt_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct device *dev = &pdev->dev;
	struct cpt_device *cpt;
	int err;

	if (num_vfs > 16 || num_vfs < 4) {
		dev_warn(dev, "Invalid vf count %d, Resetting it to 4(default)\n",
			 num_vfs);
		num_vfs = 4;
	}

	cpt = devm_kzalloc(dev, sizeof(*cpt), GFP_KERNEL);
	if (!cpt)
		return -ENOMEM;

	pci_set_drvdata(pdev, cpt);
	cpt->pdev = pdev;
	err = pci_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, NULL);
		return err;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		goto cpt_err_disable_device;
	}

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get usable DMA configuration\n");
		goto cpt_err_release_regions;
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get 48-bit DMA for consistent allocations\n");
		goto cpt_err_release_regions;
	}

	/* MAP PF's configuration registers */
	cpt->reg_base = pcim_iomap(pdev, 0, 0);
	if (!cpt->reg_base) {
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		goto cpt_err_release_regions;
	}

	/* CPT device HW initialization */
	cpt_device_init(cpt);

	/* Register interrupts */
	err = cpt_register_interrupts(cpt);
	if (err)
		goto cpt_err_release_regions;

	err = cpt_ucode_load(cpt);
	if (err)
		goto cpt_err_unregister_interrupts;

	/* Configure SRIOV */
	err = cpt_sriov_init(cpt, num_vfs);
	if (err)
		goto cpt_err_unregister_interrupts;

	return 0;

cpt_err_unregister_interrupts:
	cpt_unregister_interrupts(cpt);
cpt_err_release_regions:
	pci_release_regions(pdev);
cpt_err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
	return err;
}