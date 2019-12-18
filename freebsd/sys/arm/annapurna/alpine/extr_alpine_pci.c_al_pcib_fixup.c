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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AL_PCI_APP_CONTROL ; 
 int /*<<< orphan*/  AL_PCI_AXI_CFG_AND_CTR_0 ; 
 scalar_t__ ANNAPURNA_VENDOR_ID ; 
 void* PCIB_READ_CONFIG (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCIB_WRITE_CONFIG (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int PCIE_AXI_PF_AXI_ATTR_OVRD_FUNC_CTRL_2_PF_VEC_PH_VEC_OVRD_FROM_AXUSER_MASK ; 
 int PCIE_AXI_PF_AXI_ATTR_OVRD_FUNC_CTRL_4_PF_VEC_MEM_ADDR54_63_SEL_TGTID_MASK ; 
 int PCIM_HDRTYPE ; 
 int PCIM_MFDEV ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int PCI_FUNCMAX ; 
 int PCI_MAXHDRTYPE ; 
 int PCI_SLOTMAX ; 

__attribute__((used)) static void
al_pcib_fixup(device_t dev)
{
	uint32_t val;
	uint16_t vid;
	uint8_t hdrtype;
	int bus, slot, func, maxfunc;

	/* Fixup is only needed on bus 0 */
	bus = 0;
	for (slot = 0; slot <= PCI_SLOTMAX; slot++) {
		maxfunc = 0;
		for (func = 0; func <= maxfunc; func++) {
			hdrtype = PCIB_READ_CONFIG(dev, bus, slot, func,
			    PCIR_HDRTYPE, 1);

			if ((hdrtype & PCIM_HDRTYPE) > PCI_MAXHDRTYPE)
				continue;

			if (func == 0 && (hdrtype & PCIM_MFDEV) != 0)
				maxfunc = PCI_FUNCMAX;

			vid = PCIB_READ_CONFIG(dev, bus, slot, func,
			    PCIR_VENDOR, 2);
			if (vid == ANNAPURNA_VENDOR_ID) {
				val = PCIB_READ_CONFIG(dev, bus, slot, func,
				    AL_PCI_AXI_CFG_AND_CTR_0, 4);
				val |= PCIE_AXI_PF_AXI_ATTR_OVRD_FUNC_CTRL_2_PF_VEC_PH_VEC_OVRD_FROM_AXUSER_MASK;
				PCIB_WRITE_CONFIG(dev, bus, slot, func,
				    AL_PCI_AXI_CFG_AND_CTR_0, val, 4);

				val = PCIB_READ_CONFIG(dev, bus, slot, func,
				    AL_PCI_APP_CONTROL, 4);
				val &= ~0xffff;
				val |= PCIE_AXI_PF_AXI_ATTR_OVRD_FUNC_CTRL_4_PF_VEC_MEM_ADDR54_63_SEL_TGTID_MASK;
				PCIB_WRITE_CONFIG(dev, bus, slot, func,
				    AL_PCI_APP_CONTROL, val, 4);
			}
		}
	}
}