#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ vendor; unsigned short device; unsigned short revision; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct iso_context {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; int /*<<< orphan*/  index; } ;
struct fw_ohci {int quirks; unsigned long long ir_context_channels; int ir_context_support; int ir_context_mask; int n_ir; int it_context_support; int it_context_mask; int n_it; int /*<<< orphan*/ * registers; scalar_t__ misc_buffer_bus; scalar_t__ misc_buffer; TYPE_2__ card; int /*<<< orphan*/  ar_request_ctx; int /*<<< orphan*/  ar_response_ctx; int /*<<< orphan*/  at_request_ctx; int /*<<< orphan*/  at_response_ctx; struct fw_ohci* it_context_list; struct fw_ohci* ir_context_list; scalar_t__ self_id_bus; scalar_t__ self_id; int /*<<< orphan*/  bus_reset_work; int /*<<< orphan*/  phy_reg_mutex; int /*<<< orphan*/  lock; } ;
struct descriptor {int dummy; } ;
struct TYPE_5__ {scalar_t__ vendor; unsigned short device; unsigned short revision; int flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int AR_BUFFERS ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  OHCI1394_AsReqRcvContextControlSet ; 
 int /*<<< orphan*/  OHCI1394_AsReqTrContextControlSet ; 
 int /*<<< orphan*/  OHCI1394_AsRspRcvContextControlSet ; 
 int /*<<< orphan*/  OHCI1394_AsRspTrContextControlSet ; 
 int /*<<< orphan*/  OHCI1394_BusOptions ; 
 int /*<<< orphan*/  OHCI1394_GUIDHi ; 
 int /*<<< orphan*/  OHCI1394_GUIDLo ; 
 int /*<<< orphan*/  OHCI1394_IsoRecvIntMaskClear ; 
 int /*<<< orphan*/  OHCI1394_IsoRecvIntMaskSet ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitIntMaskClear ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitIntMaskSet ; 
 int /*<<< orphan*/  OHCI1394_PCI_HCI_Control ; 
 int /*<<< orphan*/  OHCI1394_PhyUpperBound ; 
 scalar_t__ OHCI1394_REGISTER_SIZE ; 
 int /*<<< orphan*/  OHCI1394_Version ; 
 int PAGE_SIZE ; 
 scalar_t__ PCI_ANY_ID ; 
 scalar_t__ PCI_VENDOR_ID_PINNACLE_SYSTEMS ; 
 int QUIRK_NO_MSI ; 
 int SELF_ID_BUF_SIZE ; 
 int ar_context_init (int /*<<< orphan*/ *,struct fw_ohci*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar_context_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_reset_work ; 
 int context_init (int /*<<< orphan*/ *,struct fw_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fw_ohci*) ; 
 int fw_card_add (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  fw_card_initialize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_at_packet ; 
 void* hweight32 (int) ; 
 int /*<<< orphan*/  irq_handler ; 
 int /*<<< orphan*/  kfree (struct fw_ohci*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ohci_driver ; 
 int /*<<< orphan*/  ohci_driver_name ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*,...) ; 
 int /*<<< orphan*/  ohci_notice (struct fw_ohci*,char*,...) ; 
 TYPE_1__* ohci_quirks ; 
 int param_quirks ; 
 scalar_t__ pci_dev_msi_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/ * pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fw_ohci*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmac_ohci_off (struct pci_dev*) ; 
 int /*<<< orphan*/  pmac_ohci_on (struct pci_dev*) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fw_ohci*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pci_probe(struct pci_dev *dev,
			       const struct pci_device_id *ent)
{
	struct fw_ohci *ohci;
	u32 bus_options, max_receive, link_speed, version;
	u64 guid;
	int i, err;
	size_t size;

	if (dev->vendor == PCI_VENDOR_ID_PINNACLE_SYSTEMS) {
		dev_err(&dev->dev, "Pinnacle MovieBoard is not yet supported\n");
		return -ENOSYS;
	}

	ohci = kzalloc(sizeof(*ohci), GFP_KERNEL);
	if (ohci == NULL) {
		err = -ENOMEM;
		goto fail;
	}

	fw_card_initialize(&ohci->card, &ohci_driver, &dev->dev);

	pmac_ohci_on(dev);

	err = pci_enable_device(dev);
	if (err) {
		dev_err(&dev->dev, "failed to enable OHCI hardware\n");
		goto fail_free;
	}

	pci_set_master(dev);
	pci_write_config_dword(dev, OHCI1394_PCI_HCI_Control, 0);
	pci_set_drvdata(dev, ohci);

	spin_lock_init(&ohci->lock);
	mutex_init(&ohci->phy_reg_mutex);

	INIT_WORK(&ohci->bus_reset_work, bus_reset_work);

	if (!(pci_resource_flags(dev, 0) & IORESOURCE_MEM) ||
	    pci_resource_len(dev, 0) < OHCI1394_REGISTER_SIZE) {
		ohci_err(ohci, "invalid MMIO resource\n");
		err = -ENXIO;
		goto fail_disable;
	}

	err = pci_request_region(dev, 0, ohci_driver_name);
	if (err) {
		ohci_err(ohci, "MMIO resource unavailable\n");
		goto fail_disable;
	}

	ohci->registers = pci_iomap(dev, 0, OHCI1394_REGISTER_SIZE);
	if (ohci->registers == NULL) {
		ohci_err(ohci, "failed to remap registers\n");
		err = -ENXIO;
		goto fail_iomem;
	}

	for (i = 0; i < ARRAY_SIZE(ohci_quirks); i++)
		if ((ohci_quirks[i].vendor == dev->vendor) &&
		    (ohci_quirks[i].device == (unsigned short)PCI_ANY_ID ||
		     ohci_quirks[i].device == dev->device) &&
		    (ohci_quirks[i].revision == (unsigned short)PCI_ANY_ID ||
		     ohci_quirks[i].revision >= dev->revision)) {
			ohci->quirks = ohci_quirks[i].flags;
			break;
		}
	if (param_quirks)
		ohci->quirks = param_quirks;

	/*
	 * Because dma_alloc_coherent() allocates at least one page,
	 * we save space by using a common buffer for the AR request/
	 * response descriptors and the self IDs buffer.
	 */
	BUILD_BUG_ON(AR_BUFFERS * sizeof(struct descriptor) > PAGE_SIZE/4);
	BUILD_BUG_ON(SELF_ID_BUF_SIZE > PAGE_SIZE/2);
	ohci->misc_buffer = dma_alloc_coherent(ohci->card.device,
					       PAGE_SIZE,
					       &ohci->misc_buffer_bus,
					       GFP_KERNEL);
	if (!ohci->misc_buffer) {
		err = -ENOMEM;
		goto fail_iounmap;
	}

	err = ar_context_init(&ohci->ar_request_ctx, ohci, 0,
			      OHCI1394_AsReqRcvContextControlSet);
	if (err < 0)
		goto fail_misc_buf;

	err = ar_context_init(&ohci->ar_response_ctx, ohci, PAGE_SIZE/4,
			      OHCI1394_AsRspRcvContextControlSet);
	if (err < 0)
		goto fail_arreq_ctx;

	err = context_init(&ohci->at_request_ctx, ohci,
			   OHCI1394_AsReqTrContextControlSet, handle_at_packet);
	if (err < 0)
		goto fail_arrsp_ctx;

	err = context_init(&ohci->at_response_ctx, ohci,
			   OHCI1394_AsRspTrContextControlSet, handle_at_packet);
	if (err < 0)
		goto fail_atreq_ctx;

	reg_write(ohci, OHCI1394_IsoRecvIntMaskSet, ~0);
	ohci->ir_context_channels = ~0ULL;
	ohci->ir_context_support = reg_read(ohci, OHCI1394_IsoRecvIntMaskSet);
	reg_write(ohci, OHCI1394_IsoRecvIntMaskClear, ~0);
	ohci->ir_context_mask = ohci->ir_context_support;
	ohci->n_ir = hweight32(ohci->ir_context_mask);
	size = sizeof(struct iso_context) * ohci->n_ir;
	ohci->ir_context_list = kzalloc(size, GFP_KERNEL);

	reg_write(ohci, OHCI1394_IsoXmitIntMaskSet, ~0);
	ohci->it_context_support = reg_read(ohci, OHCI1394_IsoXmitIntMaskSet);
	/* JMicron JMB38x often shows 0 at first read, just ignore it */
	if (!ohci->it_context_support) {
		ohci_notice(ohci, "overriding IsoXmitIntMask\n");
		ohci->it_context_support = 0xf;
	}
	reg_write(ohci, OHCI1394_IsoXmitIntMaskClear, ~0);
	ohci->it_context_mask = ohci->it_context_support;
	ohci->n_it = hweight32(ohci->it_context_mask);
	size = sizeof(struct iso_context) * ohci->n_it;
	ohci->it_context_list = kzalloc(size, GFP_KERNEL);

	if (ohci->it_context_list == NULL || ohci->ir_context_list == NULL) {
		err = -ENOMEM;
		goto fail_contexts;
	}

	ohci->self_id     = ohci->misc_buffer     + PAGE_SIZE/2;
	ohci->self_id_bus = ohci->misc_buffer_bus + PAGE_SIZE/2;

	bus_options = reg_read(ohci, OHCI1394_BusOptions);
	max_receive = (bus_options >> 12) & 0xf;
	link_speed = bus_options & 0x7;
	guid = ((u64) reg_read(ohci, OHCI1394_GUIDHi) << 32) |
		reg_read(ohci, OHCI1394_GUIDLo);

	if (!(ohci->quirks & QUIRK_NO_MSI))
		pci_enable_msi(dev);
	if (request_irq(dev->irq, irq_handler,
			pci_dev_msi_enabled(dev) ? 0 : IRQF_SHARED,
			ohci_driver_name, ohci)) {
		ohci_err(ohci, "failed to allocate interrupt %d\n", dev->irq);
		err = -EIO;
		goto fail_msi;
	}

	err = fw_card_add(&ohci->card, max_receive, link_speed, guid);
	if (err)
		goto fail_irq;

	version = reg_read(ohci, OHCI1394_Version) & 0x00ff00ff;
	ohci_notice(ohci,
		    "added OHCI v%x.%x device as card %d, "
		    "%d IR + %d IT contexts, quirks 0x%x%s\n",
		    version >> 16, version & 0xff, ohci->card.index,
		    ohci->n_ir, ohci->n_it, ohci->quirks,
		    reg_read(ohci, OHCI1394_PhyUpperBound) ?
			", physUB" : "");

	return 0;

 fail_irq:
	free_irq(dev->irq, ohci);
 fail_msi:
	pci_disable_msi(dev);
 fail_contexts:
	kfree(ohci->ir_context_list);
	kfree(ohci->it_context_list);
	context_release(&ohci->at_response_ctx);
 fail_atreq_ctx:
	context_release(&ohci->at_request_ctx);
 fail_arrsp_ctx:
	ar_context_release(&ohci->ar_response_ctx);
 fail_arreq_ctx:
	ar_context_release(&ohci->ar_request_ctx);
 fail_misc_buf:
	dma_free_coherent(ohci->card.device, PAGE_SIZE,
			  ohci->misc_buffer, ohci->misc_buffer_bus);
 fail_iounmap:
	pci_iounmap(dev, ohci->registers);
 fail_iomem:
	pci_release_region(dev, 0);
 fail_disable:
	pci_disable_device(dev);
 fail_free:
	kfree(ohci);
	pmac_ohci_off(dev);
 fail:
	return err;
}