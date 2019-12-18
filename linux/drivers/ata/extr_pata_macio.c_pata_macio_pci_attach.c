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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct pata_macio_priv {int /*<<< orphan*/ * dev; struct pci_dev* pdev; int /*<<< orphan*/  node; } ;
struct device_node {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pata_macio_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 scalar_t__ pata_macio_common_init (struct pata_macio_priv*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 scalar_t__ pci_request_regions (struct pci_dev*,char*) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pcim_enable_device (struct pci_dev*) ; 

__attribute__((used)) static int pata_macio_pci_attach(struct pci_dev *pdev,
				 const struct pci_device_id *id)
{
	struct pata_macio_priv	*priv;
	struct device_node	*np;
	resource_size_t		rbase;

	/* We cannot use a MacIO controller without its OF device node */
	np = pci_device_to_OF_node(pdev);
	if (np == NULL) {
		dev_err(&pdev->dev,
			"Cannot find OF device node for controller\n");
		return -ENODEV;
	}

	/* Check that it can be enabled */
	if (pcim_enable_device(pdev)) {
		dev_err(&pdev->dev,
			"Cannot enable controller PCI device\n");
		return -ENXIO;
	}

	/* Allocate and init private data structure */
	priv = devm_kzalloc(&pdev->dev,
			    sizeof(struct pata_macio_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->node = of_node_get(np);
	priv->pdev = pdev;
	priv->dev = &pdev->dev;

	/* Get MMIO regions */
	if (pci_request_regions(pdev, "pata-macio")) {
		dev_err(&pdev->dev,
			"Cannot obtain PCI resources\n");
		return -EBUSY;
	}

	/* Get register addresses and call common initialization */
	rbase = pci_resource_start(pdev, 0);
	if (pata_macio_common_init(priv,
				   rbase + 0x2000,	/* Taskfile regs */
				   rbase + 0x1000,	/* DBDMA regs */
				   rbase,		/* Feature control */
				   pdev->irq))
		return -ENXIO;

	return 0;
}