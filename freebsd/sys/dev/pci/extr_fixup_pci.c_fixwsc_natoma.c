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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
fixwsc_natoma(device_t dev)
{
    int		pmccfg;

    pmccfg = pci_read_config(dev, 0x50, 2);
#if defined(SMP)
    if (pmccfg & 0x8000) {
	device_printf(dev, "correcting Natoma config for SMP\n");
	pmccfg &= ~0x8000;
	pci_write_config(dev, 0x50, pmccfg, 2);
    }
#else
    if ((pmccfg & 0x8000) == 0) {
	device_printf(dev, "correcting Natoma config for non-SMP\n");
	pmccfg |= 0x8000;
	pci_write_config(dev, 0x50, pmccfg, 2);
    }
#endif
}