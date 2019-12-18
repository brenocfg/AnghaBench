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
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  qchunksize; } ;
struct cpt_vf {int vfgrp; int priority; struct pci_dev* pdev; TYPE_1__ cqinfo; int /*<<< orphan*/  node; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_CMD_QCHUNK_SIZE ; 
 int /*<<< orphan*/  CPT_CMD_QLEN ; 
 int /*<<< orphan*/  CPT_FLAG_VF_DRIVER ; 
 int /*<<< orphan*/  CPT_NUM_QS_PER_VF ; 
 int /*<<< orphan*/  CPT_VF_INT_VEC_E_DONE ; 
 int /*<<< orphan*/  CPT_VF_INT_VEC_E_MISC ; 
 int /*<<< orphan*/  CPT_VF_MSIX_VECTORS ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int cptvf_check_pf_ready (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_device_init (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_done_intr_handler ; 
 int /*<<< orphan*/  cptvf_enable_done_interrupts (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_enable_mbox_interrupts (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_enable_swerr_interrupts (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_free_irq_affinity (struct cpt_vf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cptvf_misc_intr_handler ; 
 int cptvf_send_vf_priority_msg (struct cpt_vf*) ; 
 int cptvf_send_vf_to_grp_msg (struct cpt_vf*) ; 
 int cptvf_send_vf_up (struct cpt_vf*) ; 
 int cptvf_send_vq_size_msg (struct cpt_vf*) ; 
 int /*<<< orphan*/  cptvf_set_irq_affinity (struct cpt_vf*,int /*<<< orphan*/ ) ; 
 int cptvf_sw_init (struct cpt_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cvm_crypto_init (struct cpt_vf*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 struct cpt_vf* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cpt_vf*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct cpt_vf*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cpt_vf*) ; 

__attribute__((used)) static int cptvf_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct device *dev = &pdev->dev;
	struct cpt_vf *cptvf;
	int    err;

	cptvf = devm_kzalloc(dev, sizeof(*cptvf), GFP_KERNEL);
	if (!cptvf)
		return -ENOMEM;

	pci_set_drvdata(pdev, cptvf);
	cptvf->pdev = pdev;
	err = pci_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, NULL);
		return err;
	}

	err = pci_request_regions(pdev, DRV_NAME);
	if (err) {
		dev_err(dev, "PCI request regions failed 0x%x\n", err);
		goto cptvf_err_disable_device;
	}
	/* Mark as VF driver */
	cptvf->flags |= CPT_FLAG_VF_DRIVER;
	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get usable DMA configuration\n");
		goto cptvf_err_release_regions;
	}

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(48));
	if (err) {
		dev_err(dev, "Unable to get 48-bit DMA for consistent allocations\n");
		goto cptvf_err_release_regions;
	}

	/* MAP PF's configuration registers */
	cptvf->reg_base = pcim_iomap(pdev, 0, 0);
	if (!cptvf->reg_base) {
		dev_err(dev, "Cannot map config register space, aborting\n");
		err = -ENOMEM;
		goto cptvf_err_release_regions;
	}

	cptvf->node = dev_to_node(&pdev->dev);
	err = pci_alloc_irq_vectors(pdev, CPT_VF_MSIX_VECTORS,
			CPT_VF_MSIX_VECTORS, PCI_IRQ_MSIX);
	if (err < 0) {
		dev_err(dev, "Request for #%d msix vectors failed\n",
			CPT_VF_MSIX_VECTORS);
		goto cptvf_err_release_regions;
	}

	err = request_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC),
			  cptvf_misc_intr_handler, 0, "CPT VF misc intr",
			  cptvf);
	if (err) {
		dev_err(dev, "Request misc irq failed");
		goto cptvf_free_vectors;
	}

	/* Enable mailbox interrupt */
	cptvf_enable_mbox_interrupts(cptvf);
	cptvf_enable_swerr_interrupts(cptvf);

	/* Check ready with PF */
	/* Gets chip ID / device Id from PF if ready */
	err = cptvf_check_pf_ready(cptvf);
	if (err) {
		dev_err(dev, "PF not responding to READY msg");
		goto cptvf_free_misc_irq;
	}

	/* CPT VF software resources initialization */
	cptvf->cqinfo.qchunksize = CPT_CMD_QCHUNK_SIZE;
	err = cptvf_sw_init(cptvf, CPT_CMD_QLEN, CPT_NUM_QS_PER_VF);
	if (err) {
		dev_err(dev, "cptvf_sw_init() failed");
		goto cptvf_free_misc_irq;
	}
	/* Convey VQ LEN to PF */
	err = cptvf_send_vq_size_msg(cptvf);
	if (err) {
		dev_err(dev, "PF not responding to QLEN msg");
		goto cptvf_free_misc_irq;
	}

	/* CPT VF device initialization */
	cptvf_device_init(cptvf);
	/* Send msg to PF to assign currnet Q to required group */
	cptvf->vfgrp = 1;
	err = cptvf_send_vf_to_grp_msg(cptvf);
	if (err) {
		dev_err(dev, "PF not responding to VF_GRP msg");
		goto cptvf_free_misc_irq;
	}

	cptvf->priority = 1;
	err = cptvf_send_vf_priority_msg(cptvf);
	if (err) {
		dev_err(dev, "PF not responding to VF_PRIO msg");
		goto cptvf_free_misc_irq;
	}

	err = request_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_DONE),
			  cptvf_done_intr_handler, 0, "CPT VF done intr",
			  cptvf);
	if (err) {
		dev_err(dev, "Request done irq failed\n");
		goto cptvf_free_misc_irq;
	}

	/* Enable mailbox interrupt */
	cptvf_enable_done_interrupts(cptvf);

	/* Set irq affinity masks */
	cptvf_set_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
	cptvf_set_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);

	err = cptvf_send_vf_up(cptvf);
	if (err) {
		dev_err(dev, "PF not responding to UP msg");
		goto cptvf_free_irq_affinity;
	}
	err = cvm_crypto_init(cptvf);
	if (err) {
		dev_err(dev, "Algorithm register failed\n");
		goto cptvf_free_irq_affinity;
	}
	return 0;

cptvf_free_irq_affinity:
	cptvf_free_irq_affinity(cptvf, CPT_VF_INT_VEC_E_DONE);
	cptvf_free_irq_affinity(cptvf, CPT_VF_INT_VEC_E_MISC);
cptvf_free_misc_irq:
	free_irq(pci_irq_vector(pdev, CPT_VF_INT_VEC_E_MISC), cptvf);
cptvf_free_vectors:
	pci_free_irq_vectors(cptvf->pdev);
cptvf_err_release_regions:
	pci_release_regions(pdev);
cptvf_err_disable_device:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	return err;
}