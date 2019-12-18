#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct thunderx_ocx {scalar_t__ regs; int /*<<< orphan*/  debugfs; TYPE_2__* msix_ent; struct pci_dev* pdev; scalar_t__ link_ring_tail; scalar_t__ link_ring_head; scalar_t__ com_ring_tail; scalar_t__ com_ring_head; struct edac_device_ctl_info* edac_dev; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_1__ kobj; } ;
struct pci_dev {TYPE_3__ dev; } ;
struct edac_device_ctl_info {char* mod_name; char* ctl_name; int /*<<< orphan*/  dev_name; TYPE_3__* dev; struct thunderx_ocx* pvt_info; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_9__ {int entry; scalar_t__ vector; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_EDAC_DEBUG ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ OCX_COM_INT ; 
 int /*<<< orphan*/  OCX_COM_INT_ENA_ALL ; 
 scalar_t__ OCX_COM_INT_ENA_W1S ; 
 scalar_t__ OCX_COM_LINKX_INT (int) ; 
 int /*<<< orphan*/  OCX_COM_LINKX_INT_ENA_ALL ; 
 scalar_t__ OCX_COM_LINKX_INT_ENA_W1S (int) ; 
 int OCX_INTS ; 
 int OCX_LINK_INTS ; 
 scalar_t__ OCX_LNE_INT (int) ; 
 scalar_t__ OCX_LNE_INT_EN (int) ; 
 int /*<<< orphan*/  OCX_LNE_INT_ENA_ALL ; 
 int OCX_RX_LANES ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*,int,char*) ; 
 int devm_request_threaded_irq (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  edac_debugfs_create_dir (int /*<<< orphan*/ ) ; 
 int edac_device_add_device (struct edac_device_ctl_info*) ; 
 struct edac_device_ctl_info* edac_device_alloc_ctl_info (int,char*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int edac_device_alloc_index () ; 
 int /*<<< orphan*/  edac_device_free_ctl_info (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  ocx_dfs_ents ; 
 int pci_enable_msix_exact (struct pci_dev*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct edac_device_ctl_info*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int thunderx_create_debugfs_nodes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thunderx_ocx*,int) ; 
 int /*<<< orphan*/  thunderx_ocx_clearstats (struct thunderx_ocx*) ; 
 int /*<<< orphan*/  thunderx_ocx_com_isr ; 
 int /*<<< orphan*/  thunderx_ocx_com_threaded_isr ; 
 int /*<<< orphan*/  thunderx_ocx_lnk_isr ; 
 int /*<<< orphan*/  thunderx_ocx_lnk_threaded_isr ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int thunderx_ocx_probe(struct pci_dev *pdev,
			      const struct pci_device_id *id)
{
	struct thunderx_ocx *ocx;
	struct edac_device_ctl_info *edac_dev;
	char name[32];
	int idx;
	int i;
	int ret;
	u64 reg;

	ret = pcim_enable_device(pdev);
	if (ret) {
		dev_err(&pdev->dev, "Cannot enable PCI device: %d\n", ret);
		return ret;
	}

	ret = pcim_iomap_regions(pdev, BIT(0), "thunderx_ocx");
	if (ret) {
		dev_err(&pdev->dev, "Cannot map PCI resources: %d\n", ret);
		return ret;
	}

	idx = edac_device_alloc_index();
	snprintf(name, sizeof(name), "OCX%d", idx);
	edac_dev = edac_device_alloc_ctl_info(sizeof(struct thunderx_ocx),
					      name, 1, "CCPI", 1,
					      0, NULL, 0, idx);
	if (!edac_dev) {
		dev_err(&pdev->dev, "Cannot allocate EDAC device: %d\n", ret);
		return -ENOMEM;
	}
	ocx = edac_dev->pvt_info;
	ocx->edac_dev = edac_dev;
	ocx->com_ring_head = 0;
	ocx->com_ring_tail = 0;
	ocx->link_ring_head = 0;
	ocx->link_ring_tail = 0;

	ocx->regs = pcim_iomap_table(pdev)[0];
	if (!ocx->regs) {
		dev_err(&pdev->dev, "Cannot map PCI resources: %d\n", ret);
		ret = -ENODEV;
		goto err_free;
	}

	ocx->pdev = pdev;

	for (i = 0; i < OCX_INTS; i++) {
		ocx->msix_ent[i].entry = i;
		ocx->msix_ent[i].vector = 0;
	}

	ret = pci_enable_msix_exact(pdev, ocx->msix_ent, OCX_INTS);
	if (ret) {
		dev_err(&pdev->dev, "Cannot enable interrupt: %d\n", ret);
		goto err_free;
	}

	for (i = 0; i < OCX_INTS; i++) {
		ret = devm_request_threaded_irq(&pdev->dev,
						ocx->msix_ent[i].vector,
						(i == 3) ?
						 thunderx_ocx_com_isr :
						 thunderx_ocx_lnk_isr,
						(i == 3) ?
						 thunderx_ocx_com_threaded_isr :
						 thunderx_ocx_lnk_threaded_isr,
						0, "[EDAC] ThunderX OCX",
						&ocx->msix_ent[i]);
		if (ret)
			goto err_free;
	}

	edac_dev->dev = &pdev->dev;
	edac_dev->dev_name = dev_name(&pdev->dev);
	edac_dev->mod_name = "thunderx-ocx";
	edac_dev->ctl_name = "thunderx-ocx";

	ret = edac_device_add_device(edac_dev);
	if (ret) {
		dev_err(&pdev->dev, "Cannot add EDAC device: %d\n", ret);
		goto err_free;
	}

	if (IS_ENABLED(CONFIG_EDAC_DEBUG)) {
		ocx->debugfs = edac_debugfs_create_dir(pdev->dev.kobj.name);

		ret = thunderx_create_debugfs_nodes(ocx->debugfs,
						    ocx_dfs_ents,
						    ocx,
						    ARRAY_SIZE(ocx_dfs_ents));
		if (ret != ARRAY_SIZE(ocx_dfs_ents)) {
			dev_warn(&pdev->dev, "Error creating debugfs entries: %d%s\n",
				 ret, ret >= 0 ? " created" : "");
		}
	}

	pci_set_drvdata(pdev, edac_dev);

	thunderx_ocx_clearstats(ocx);

	for (i = 0; i < OCX_RX_LANES; i++) {
		writeq(OCX_LNE_INT_ENA_ALL,
		       ocx->regs + OCX_LNE_INT_EN(i));

		reg = readq(ocx->regs + OCX_LNE_INT(i));
		writeq(reg, ocx->regs + OCX_LNE_INT(i));

	}

	for (i = 0; i < OCX_LINK_INTS; i++) {
		reg = readq(ocx->regs + OCX_COM_LINKX_INT(i));
		writeq(reg, ocx->regs + OCX_COM_LINKX_INT(i));

		writeq(OCX_COM_LINKX_INT_ENA_ALL,
		       ocx->regs + OCX_COM_LINKX_INT_ENA_W1S(i));
	}

	reg = readq(ocx->regs + OCX_COM_INT);
	writeq(reg, ocx->regs + OCX_COM_INT);

	writeq(OCX_COM_INT_ENA_ALL, ocx->regs + OCX_COM_INT_ENA_W1S);

	return 0;
err_free:
	edac_device_free_ctl_info(edac_dev);

	return ret;
}