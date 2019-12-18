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
typedef  int u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int LASAT_IRQ_ETH0 ; 
 int LASAT_IRQ_ETH1 ; 
 int LASAT_IRQ_HDC ; 
 int /*<<< orphan*/  LASAT_IRQ_PCIA ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	switch (slot) {
	case 1:
	case 2:
	case 3:
		return LASAT_IRQ_PCIA + (((slot-1) + (pin-1)) % 4);
	case 4:
		return LASAT_IRQ_ETH1;	 /* Ethernet 1 (LAN 2) */
	case 5:
		return LASAT_IRQ_ETH0;	 /* Ethernet 0 (LAN 1) */
	case 6:
		return LASAT_IRQ_HDC;	 /* IDE controller */
	default:
		return 0xff;		/* Illegal */
	}

	return -1;
}