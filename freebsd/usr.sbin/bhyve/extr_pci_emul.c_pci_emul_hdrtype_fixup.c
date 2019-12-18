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
typedef  int uint32_t ;

/* Variables and functions */
 int PCIM_MFDEV ; 
 int PCIR_HDRTYPE ; 
 int pci_emul_is_mfdev (int,int) ; 

__attribute__((used)) static void
pci_emul_hdrtype_fixup(int bus, int slot, int off, int bytes, uint32_t *rv)
{
	int mfdev;

	if (off <= PCIR_HDRTYPE && off + bytes > PCIR_HDRTYPE) {
		mfdev = pci_emul_is_mfdev(bus, slot);
		switch (bytes) {
		case 1:
		case 2:
			*rv &= ~PCIM_MFDEV;
			if (mfdev) {
				*rv |= PCIM_MFDEV;
			}
			break;
		case 4:
			*rv &= ~(PCIM_MFDEV << 16);
			if (mfdev) {
				*rv |= (PCIM_MFDEV << 16);
			}
			break;
		}
	}
}