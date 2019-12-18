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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 unsigned int PCI_FUNCMAX ; 
 unsigned int PCI_SLOTMAX ; 
 unsigned int octopci_init_device (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int octopci_read_config (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned
octopci_init_bus(device_t dev, unsigned b)
{
	unsigned s, f;
	uint8_t hdrtype;
	unsigned secbus;

	secbus = b;

	for (s = 0; s <= PCI_SLOTMAX; s++) {
		for (f = 0; f <= PCI_FUNCMAX; f++) {
			hdrtype = octopci_read_config(dev, b, s, f, PCIR_HDRTYPE, 1);

			if (hdrtype == 0xff) {
				if (f == 0)
					break; /* Next slot.  */
				continue; /* Next function.  */
			}

			secbus = octopci_init_device(dev, b, s, f, secbus);

			if (f == 0 && (hdrtype & PCIM_MFDEV) == 0)
				break; /* Next slot.  */
		}
	}

	return (secbus);
}