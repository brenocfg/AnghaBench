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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int (* read ) (unsigned int,unsigned int,unsigned int,int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  WARN_ON (unsigned int) ; 
 int /*<<< orphan*/  ac97_hdr ; 
 int /*<<< orphan*/  aes_hdr ; 
 int /*<<< orphan*/  ehci_hdr ; 
 int /*<<< orphan*/  ff_loc ; 
 int /*<<< orphan*/  gxfb_hdr ; 
 int /*<<< orphan*/  gxnb_hdr ; 
 int /*<<< orphan*/ * hdr_addr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_lx ; 
 int /*<<< orphan*/  is_simulated (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  isa_hdr ; 
 int /*<<< orphan*/  lxfb_hdr ; 
 int /*<<< orphan*/  lxnb_hdr ; 
 int /*<<< orphan*/  ohci_hdr ; 
 TYPE_1__ pci_direct_conf1 ; 
 int stub1 (unsigned int,unsigned int,unsigned int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_loc ; 

__attribute__((used)) static int pci_olpc_read(unsigned int seg, unsigned int bus,
		unsigned int devfn, int reg, int len, uint32_t *value)
{
	uint32_t *addr;

	WARN_ON(seg);

	/* Use the hardware mechanism for non-simulated devices */
	if (!is_simulated(bus, devfn))
		return pci_direct_conf1.read(seg, bus, devfn, reg, len, value);

	/*
	 * No device has config registers past 0x70, so we save table space
	 * by not storing entries for the nonexistent registers
	 */
	if (reg >= 0x70)
		addr = &zero_loc;
	else {
		switch (devfn) {
		case  0x8:
			addr = hdr_addr(is_lx ? lxnb_hdr : gxnb_hdr, reg);
			break;
		case  0x9:
			addr = hdr_addr(is_lx ? lxfb_hdr : gxfb_hdr, reg);
			break;
		case  0xa:
			addr = is_lx ? hdr_addr(aes_hdr, reg) : &ff_loc;
			break;
		case 0x78:
			addr = hdr_addr(isa_hdr, reg);
			break;
		case 0x7b:
			addr = hdr_addr(ac97_hdr, reg);
			break;
		case 0x7c:
			addr = hdr_addr(ohci_hdr, reg);
			break;
		case 0x7d:
			addr = hdr_addr(ehci_hdr, reg);
			break;
		default:
			addr = &ff_loc;
			break;
		}
	}
	switch (len) {
	case 1:
		*value = *(uint8_t *)addr;
		break;
	case 2:
		*value = *(uint16_t *)addr;
		break;
	case 4:
		*value = *addr;
		break;
	default:
		BUG();
	}

	return 0;
}