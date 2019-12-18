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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pa_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_RTY_TOUT ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  UBS_DEF_CACHELINE ; 
 int UBS_DEF_RTY ; 
 int UBS_DEF_TOUT ; 
 int UBS_PCI_RTY_MASK ; 
 int UBS_PCI_RTY_SHIFT ; 
 int UBS_PCI_TOUT_MASK ; 
 int UBS_PCI_TOUT_SHIFT ; 
 TYPE_1__* pa ; 
 int /*<<< orphan*/  pc ; 
 int pci_conf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_conf_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ubsec_init_pciregs(device_t dev)
{
#if 0
	u_int32_t misc;

	misc = pci_conf_read(pc, pa->pa_tag, BS_RTY_TOUT);
	misc = (misc & ~(UBS_PCI_RTY_MASK << UBS_PCI_RTY_SHIFT))
	    | ((UBS_DEF_RTY & 0xff) << UBS_PCI_RTY_SHIFT);
	misc = (misc & ~(UBS_PCI_TOUT_MASK << UBS_PCI_TOUT_SHIFT))
	    | ((UBS_DEF_TOUT & 0xff) << UBS_PCI_TOUT_SHIFT);
	pci_conf_write(pc, pa->pa_tag, BS_RTY_TOUT, misc);
#endif

	/*
	 * This will set the cache line size to 1, this will
	 * force the BCM58xx chip just to do burst read/writes.
	 * Cache line read/writes are to slow
	 */
	pci_write_config(dev, PCIR_CACHELNSZ, UBS_DEF_CACHELINE, 1);
}