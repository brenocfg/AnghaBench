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
struct xenisrc {int xi_pirq; int xi_edgetrigger; } ;
struct physdev_map_pirq {int index; int pirq; int bus; int devfn; int entry_nr; int /*<<< orphan*/  type; int /*<<< orphan*/  domid; } ;
typedef  int /*<<< orphan*/  msi_irq ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  EVTCHN_TYPE_PIRQ ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_map_pirq*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAP_PIRQ_TYPE_MSI_SEG ; 
 int /*<<< orphan*/  MAP_PIRQ_TYPE_MULTI_MSI ; 
 int /*<<< orphan*/  PHYSDEVOP_map_pirq ; 
 int /*<<< orphan*/  memset (struct physdev_map_pirq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int,int) ; 
 int pci_get_bus (int /*<<< orphan*/ ) ; 
 int pci_get_domain (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 struct xenisrc* xen_intr_alloc_isrc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xen_intr_isrc_lock ; 

int
xen_register_msi(device_t dev, int vector, int count)
{
	struct physdev_map_pirq msi_irq;
	struct xenisrc *isrc;
	int ret;

	memset(&msi_irq, 0, sizeof(msi_irq));
	msi_irq.domid = DOMID_SELF;
	msi_irq.type = count == 1 ?
	    MAP_PIRQ_TYPE_MSI_SEG : MAP_PIRQ_TYPE_MULTI_MSI;
	msi_irq.index = -1;
	msi_irq.pirq = -1;
	msi_irq.bus = pci_get_bus(dev) | (pci_get_domain(dev) << 16);
	msi_irq.devfn = (pci_get_slot(dev) << 3) | pci_get_function(dev);
	msi_irq.entry_nr = count;

	ret = HYPERVISOR_physdev_op(PHYSDEVOP_map_pirq, &msi_irq);
	if (ret != 0)
		return (ret);
	if (count != msi_irq.entry_nr) {
		panic("unable to setup all requested MSI vectors "
		    "(expected %d got %d)", count, msi_irq.entry_nr);
	}

	mtx_lock(&xen_intr_isrc_lock);
	for (int i = 0; i < count; i++) {
		isrc = xen_intr_alloc_isrc(EVTCHN_TYPE_PIRQ, vector + i);
		KASSERT(isrc != NULL,
		    ("xen: unable to allocate isrc for interrupt"));
		isrc->xi_pirq = msi_irq.pirq + i;
		/* MSI interrupts are always edge triggered */
		isrc->xi_edgetrigger = 1;
	}
	mtx_unlock(&xen_intr_isrc_lock);

	return (0);
}