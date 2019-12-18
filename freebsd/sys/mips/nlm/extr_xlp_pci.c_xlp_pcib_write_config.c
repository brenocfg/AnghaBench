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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int u_int32_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XLP_HDR_OFFSET (int /*<<< orphan*/ ,int,int,int) ; 
 int XLP_PCI_DEVSCRATCH_REG0 ; 
 int /*<<< orphan*/  nlm_pcicfg_base (int /*<<< orphan*/ ) ; 
 int nlm_read_pci_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_write_pci_reg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
xlp_pcib_write_config(device_t dev, u_int b, u_int s, u_int f,
    u_int reg, u_int32_t val, int width)
{
	uint64_t cfgaddr;
	uint32_t data = 0;
	int	regindex = reg / sizeof(uint32_t);

	cfgaddr = nlm_pcicfg_base(XLP_HDR_OFFSET(0, b, s, f));
	if ((width == 2) && (reg & 1))
		return;
	else if ((width == 4) && (reg & 3))
		return;

	if (width == 1) {
		data = nlm_read_pci_reg(cfgaddr, regindex);
		data = (data & ~(0xff << ((reg & 3) << 3))) |
		    (val << ((reg & 3) << 3));
	} else if (width == 2) {
		data = nlm_read_pci_reg(cfgaddr, regindex);
		data = (data & ~(0xffff << ((reg & 3) << 3))) |
		    (val << ((reg & 3) << 3));
	} else {
		data = val;
	}

	/*
	 * use shadow reg for intpin/intline which are dead
	 */
	if (b == 0 && regindex == 0xf && s % 8 > 1)
		regindex = XLP_PCI_DEVSCRATCH_REG0;
	nlm_write_pci_reg(cfgaddr, regindex, data);
}