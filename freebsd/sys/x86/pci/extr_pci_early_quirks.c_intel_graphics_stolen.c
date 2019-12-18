#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct intel_stolen_ops {int /*<<< orphan*/  (* size ) (int const,int const,int const) ;int /*<<< orphan*/  (* base ) (int const,int const,int const) ;} ;
struct TYPE_3__ {scalar_t__ device; struct intel_stolen_ops* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 scalar_t__ PCI_CLASS_VGA ; 
 scalar_t__ PCI_VENDOR_INTEL ; 
 int /*<<< orphan*/  intel_graphics_stolen_base ; 
 int /*<<< orphan*/  intel_graphics_stolen_size ; 
 TYPE_1__* intel_ids ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ pci_cfgregopen () ; 
 scalar_t__ pci_cfgregread (int const,int const,int const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int const,int const,int const) ; 
 int /*<<< orphan*/  stub2 (int const,int const,int const) ; 

__attribute__((used)) static void
intel_graphics_stolen(void)
{
	const struct intel_stolen_ops *ops;
	uint32_t vendor, device, class;
	int i;

	/* XXX: Scan bus instead of assuming 0:2:0? */
	const int bus = 0;
	const int slot = 2;
	const int func = 0;

	if (pci_cfgregopen() == 0)
		return;

	vendor = pci_cfgregread(bus, slot, func, PCIR_VENDOR, 2);
	if (vendor != PCI_VENDOR_INTEL)
		return;

	class = pci_cfgregread(bus, slot, func, PCIR_SUBCLASS, 2);
	if (class != PCI_CLASS_VGA)
		return;

	device = pci_cfgregread(bus, slot, func, PCIR_DEVICE, 2);
	if (device == 0xFFFF)
		return;

	for (i = 0; i < nitems(intel_ids); i++) {
		if (intel_ids[i].device != device)
			continue;
		ops = intel_ids[i].data;
		intel_graphics_stolen_base = ops->base(bus, slot, func);
		intel_graphics_stolen_size = ops->size(bus, slot, func);
		break;
	}

	/* XXX: enable this once the KPI is available */
	/* phys_avail_reserve(intel_graphics_stolen_base, */
	/*     intel_graphics_stolen_base + intel_graphics_stolen_size); */
}