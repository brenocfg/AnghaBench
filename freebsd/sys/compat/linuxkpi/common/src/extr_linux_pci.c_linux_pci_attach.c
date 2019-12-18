#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource_list_entry {int /*<<< orphan*/  start; } ;
struct pci_driver {int (* probe ) (struct pci_dev*,struct pci_device_id const*) ;scalar_t__ isdrm; } ;
struct TYPE_4__ {int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; int /*<<< orphan*/  vendor; int /*<<< orphan*/  device; } ;
struct pci_devinfo {TYPE_1__ cfg; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  kobj; int /*<<< orphan*/  irqents; int /*<<< orphan*/  bsddev; TYPE_3__* parent; } ;
struct pci_dev {TYPE_2__ dev; int /*<<< orphan*/  links; struct pci_bus* bus; int /*<<< orphan*/  irq; struct pci_driver* pdrv; int /*<<< orphan*/  revision; int /*<<< orphan*/  class; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  devfn; } ;
struct pci_bus {int /*<<< orphan*/  domain; int /*<<< orphan*/  number; struct pci_dev* self; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LINUX_IRQ_INVALID ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  curthread ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pci_dev* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct pci_devinfo*) ; 
 int /*<<< orphan*/  free (struct pci_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_dev_ktype ; 
 struct pci_driver* linux_pci_find (int /*<<< orphan*/ ,struct pci_device_id const**) ; 
 struct resource_list_entry* linux_pci_get_rle (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int linux_pdev_dma_init (struct pci_dev*) ; 
 int /*<<< orphan*/  linux_pdev_dma_uninit (struct pci_dev*) ; 
 TYPE_3__ linux_root_device ; 
 int /*<<< orphan*/  linux_set_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct pci_bus* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_devices ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lock ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct pci_dev*,struct pci_device_id const*) ; 

__attribute__((used)) static int
linux_pci_attach(device_t dev)
{
	struct resource_list_entry *rle;
	struct pci_bus *pbus;
	struct pci_dev *pdev;
	struct pci_devinfo *dinfo;
	struct pci_driver *pdrv;
	const struct pci_device_id *id;
	device_t parent;
	int error;

	linux_set_current(curthread);

	pdrv = linux_pci_find(dev, &id);
	pdev = device_get_softc(dev);

	parent = device_get_parent(dev);
	if (pdrv->isdrm) {
		dinfo = device_get_ivars(parent);
		device_set_ivars(dev, dinfo);
	} else {
		dinfo = device_get_ivars(dev);
	}

	pdev->dev.parent = &linux_root_device;
	pdev->dev.bsddev = dev;
	INIT_LIST_HEAD(&pdev->dev.irqents);
	pdev->devfn = PCI_DEVFN(pci_get_slot(dev), pci_get_function(dev));
	pdev->device = dinfo->cfg.device;
	pdev->vendor = dinfo->cfg.vendor;
	pdev->subsystem_vendor = dinfo->cfg.subvendor;
	pdev->subsystem_device = dinfo->cfg.subdevice;
	pdev->class = pci_get_class(dev);
	pdev->revision = pci_get_revid(dev);
	pdev->pdrv = pdrv;
	kobject_init(&pdev->dev.kobj, &linux_dev_ktype);
	kobject_set_name(&pdev->dev.kobj, device_get_nameunit(dev));
	kobject_add(&pdev->dev.kobj, &linux_root_device.kobj,
	    kobject_name(&pdev->dev.kobj));
	rle = linux_pci_get_rle(pdev, SYS_RES_IRQ, 0);
	if (rle != NULL)
		pdev->dev.irq = rle->start;
	else
		pdev->dev.irq = LINUX_IRQ_INVALID;
	pdev->irq = pdev->dev.irq;
	error = linux_pdev_dma_init(pdev);
	if (error)
		goto out_dma_init;

	pbus = malloc(sizeof(*pbus), M_DEVBUF, M_WAITOK | M_ZERO);
	pbus->self = pdev;
	pbus->number = pci_get_bus(dev);
	pbus->domain = pci_get_domain(dev);
	pdev->bus = pbus;

	spin_lock(&pci_lock);
	list_add(&pdev->links, &pci_devices);
	spin_unlock(&pci_lock);

	error = pdrv->probe(pdev, id);
	if (error)
		goto out_probe;
	return (0);

out_probe:
	free(pdev->bus, M_DEVBUF);
	linux_pdev_dma_uninit(pdev);
out_dma_init:
	spin_lock(&pci_lock);
	list_del(&pdev->links);
	spin_unlock(&pci_lock);
	put_device(&pdev->dev);
	return (-error);
}