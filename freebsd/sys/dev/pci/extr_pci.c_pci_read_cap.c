#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_19__ {int ht_slave; int ht_msimap; int ht_msictrl; int ht_msiaddr; } ;
struct TYPE_18__ {int ea_location; } ;
struct TYPE_17__ {int pcie_location; int pcie_type; } ;
struct TYPE_16__ {int pcix_location; } ;
struct TYPE_15__ {int vpd_reg; } ;
struct TYPE_14__ {int msix_location; int msix_ctrl; int msix_table_offset; int msix_pba_offset; void* msix_pba_bar; void* msix_table_bar; int /*<<< orphan*/  msix_msgnum; } ;
struct TYPE_13__ {int msi_location; int msi_ctrl; int msi_msgnum; } ;
struct TYPE_12__ {int pp_cap; int /*<<< orphan*/  pp_data; int /*<<< orphan*/  pp_bse; int /*<<< orphan*/  pp_status; } ;
struct TYPE_20__ {int hdrtype; int subvendor; int subdevice; TYPE_8__ ht; int /*<<< orphan*/  func; int /*<<< orphan*/  slot; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; TYPE_7__ ea; TYPE_6__ pcie; TYPE_5__ pcix; TYPE_4__ vpd; TYPE_3__ msix; TYPE_2__ msi; TYPE_1__ pp; } ;
typedef  TYPE_9__ pcicfgregs ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MSI_INTEL_ADDR_BASE ; 
 int PCICAP_ID ; 
 int PCICAP_NEXTPTR ; 
 int PCIEM_FLAGS_TYPE ; 
 int /*<<< orphan*/  PCIER_FLAGS ; 
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 140 
#define  PCIM_HDRTYPE_CARDBUS 139 
#define  PCIM_HDRTYPE_NORMAL 138 
#define  PCIM_HTCAP_MSI_MAPPING 137 
 int PCIM_HTCAP_SLAVE ; 
 int PCIM_HTCMD_CAP_MASK ; 
 int PCIM_HTCMD_MSI_ENABLE ; 
 int PCIM_HTCMD_MSI_FIXED ; 
 int PCIM_MSICTRL_MMC_MASK ; 
 int PCIM_MSIXCTRL_TABLE_SIZE ; 
 int PCIM_MSIX_BIR_MASK ; 
 void* PCIR_BAR (int) ; 
 int PCIR_CAP_PTR ; 
 int PCIR_CAP_PTR_2 ; 
 int /*<<< orphan*/  PCIR_HTMSI_ADDRESS_HI ; 
 int /*<<< orphan*/  PCIR_HTMSI_ADDRESS_LO ; 
 int PCIR_HT_COMMAND ; 
 int /*<<< orphan*/  PCIR_MSIX_CTRL ; 
 int /*<<< orphan*/  PCIR_MSIX_PBA ; 
 int /*<<< orphan*/  PCIR_MSIX_TABLE ; 
 int /*<<< orphan*/  PCIR_MSI_CTRL ; 
 int /*<<< orphan*/  PCIR_POWER_BSE ; 
 int /*<<< orphan*/  PCIR_POWER_CAP ; 
 int PCIR_POWER_DATA ; 
 int /*<<< orphan*/  PCIR_POWER_STATUS ; 
 int /*<<< orphan*/  PCIR_SUBVENDCAP_ID ; 
#define  PCIY_EA 136 
#define  PCIY_EXPRESS 135 
#define  PCIY_HT 134 
#define  PCIY_MSI 133 
#define  PCIY_MSIX 132 
#define  PCIY_PCIX 131 
#define  PCIY_PMG 130 
#define  PCIY_SUBVENDOR 129 
#define  PCIY_VPD 128 
 int REG (int,int) ; 
 int /*<<< orphan*/  WREG (int,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pci_ea_fill_info (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int pcie_chipset ; 
 int pcix_chipset ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
pci_read_cap(device_t pcib, pcicfgregs *cfg)
{
#define	REG(n, w)	PCIB_READ_CONFIG(pcib, cfg->bus, cfg->slot, cfg->func, n, w)
#define	WREG(n, v, w)	PCIB_WRITE_CONFIG(pcib, cfg->bus, cfg->slot, cfg->func, n, v, w)
#if defined(__i386__) || defined(__amd64__) || defined(__powerpc__)
	uint64_t addr;
#endif
	uint32_t val;
	int	ptr, nextptr, ptrptr;

	switch (cfg->hdrtype & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
	case PCIM_HDRTYPE_BRIDGE:
		ptrptr = PCIR_CAP_PTR;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		ptrptr = PCIR_CAP_PTR_2;	/* cardbus capabilities ptr */
		break;
	default:
		return;		/* no extended capabilities support */
	}
	nextptr = REG(ptrptr, 1);	/* sanity check? */

	/*
	 * Read capability entries.
	 */
	while (nextptr != 0) {
		/* Sanity check */
		if (nextptr > 255) {
			printf("illegal PCI extended capability offset %d\n",
			    nextptr);
			return;
		}
		/* Find the next entry */
		ptr = nextptr;
		nextptr = REG(ptr + PCICAP_NEXTPTR, 1);

		/* Process this entry */
		switch (REG(ptr + PCICAP_ID, 1)) {
		case PCIY_PMG:		/* PCI power management */
			if (cfg->pp.pp_cap == 0) {
				cfg->pp.pp_cap = REG(ptr + PCIR_POWER_CAP, 2);
				cfg->pp.pp_status = ptr + PCIR_POWER_STATUS;
				cfg->pp.pp_bse = ptr + PCIR_POWER_BSE;
				if ((nextptr - ptr) > PCIR_POWER_DATA)
					cfg->pp.pp_data = ptr + PCIR_POWER_DATA;
			}
			break;
		case PCIY_HT:		/* HyperTransport */
			/* Determine HT-specific capability type. */
			val = REG(ptr + PCIR_HT_COMMAND, 2);

			if ((val & 0xe000) == PCIM_HTCAP_SLAVE)
				cfg->ht.ht_slave = ptr;

#if defined(__i386__) || defined(__amd64__) || defined(__powerpc__)
			switch (val & PCIM_HTCMD_CAP_MASK) {
			case PCIM_HTCAP_MSI_MAPPING:
				if (!(val & PCIM_HTCMD_MSI_FIXED)) {
					/* Sanity check the mapping window. */
					addr = REG(ptr + PCIR_HTMSI_ADDRESS_HI,
					    4);
					addr <<= 32;
					addr |= REG(ptr + PCIR_HTMSI_ADDRESS_LO,
					    4);
					if (addr != MSI_INTEL_ADDR_BASE)
						device_printf(pcib,
	    "HT device at pci%d:%d:%d:%d has non-default MSI window 0x%llx\n",
						    cfg->domain, cfg->bus,
						    cfg->slot, cfg->func,
						    (long long)addr);
				} else
					addr = MSI_INTEL_ADDR_BASE;

				cfg->ht.ht_msimap = ptr;
				cfg->ht.ht_msictrl = val;
				cfg->ht.ht_msiaddr = addr;
				break;
			}
#endif
			break;
		case PCIY_MSI:		/* PCI MSI */
			cfg->msi.msi_location = ptr;
			cfg->msi.msi_ctrl = REG(ptr + PCIR_MSI_CTRL, 2);
			cfg->msi.msi_msgnum = 1 << ((cfg->msi.msi_ctrl &
						     PCIM_MSICTRL_MMC_MASK)>>1);
			break;
		case PCIY_MSIX:		/* PCI MSI-X */
			cfg->msix.msix_location = ptr;
			cfg->msix.msix_ctrl = REG(ptr + PCIR_MSIX_CTRL, 2);
			cfg->msix.msix_msgnum = (cfg->msix.msix_ctrl &
			    PCIM_MSIXCTRL_TABLE_SIZE) + 1;
			val = REG(ptr + PCIR_MSIX_TABLE, 4);
			cfg->msix.msix_table_bar = PCIR_BAR(val &
			    PCIM_MSIX_BIR_MASK);
			cfg->msix.msix_table_offset = val & ~PCIM_MSIX_BIR_MASK;
			val = REG(ptr + PCIR_MSIX_PBA, 4);
			cfg->msix.msix_pba_bar = PCIR_BAR(val &
			    PCIM_MSIX_BIR_MASK);
			cfg->msix.msix_pba_offset = val & ~PCIM_MSIX_BIR_MASK;
			break;
		case PCIY_VPD:		/* PCI Vital Product Data */
			cfg->vpd.vpd_reg = ptr;
			break;
		case PCIY_SUBVENDOR:
			/* Should always be true. */
			if ((cfg->hdrtype & PCIM_HDRTYPE) ==
			    PCIM_HDRTYPE_BRIDGE) {
				val = REG(ptr + PCIR_SUBVENDCAP_ID, 4);
				cfg->subvendor = val & 0xffff;
				cfg->subdevice = val >> 16;
			}
			break;
		case PCIY_PCIX:		/* PCI-X */
			/*
			 * Assume we have a PCI-X chipset if we have
			 * at least one PCI-PCI bridge with a PCI-X
			 * capability.  Note that some systems with
			 * PCI-express or HT chipsets might match on
			 * this check as well.
			 */
			if ((cfg->hdrtype & PCIM_HDRTYPE) ==
			    PCIM_HDRTYPE_BRIDGE)
				pcix_chipset = 1;
			cfg->pcix.pcix_location = ptr;
			break;
		case PCIY_EXPRESS:	/* PCI-express */
			/*
			 * Assume we have a PCI-express chipset if we have
			 * at least one PCI-express device.
			 */
			pcie_chipset = 1;
			cfg->pcie.pcie_location = ptr;
			val = REG(ptr + PCIER_FLAGS, 2);
			cfg->pcie.pcie_type = val & PCIEM_FLAGS_TYPE;
			break;
		case PCIY_EA:		/* Enhanced Allocation */
			cfg->ea.ea_location = ptr;
			pci_ea_fill_info(pcib, cfg);
			break;
		default:
			break;
		}
	}

#if defined(__powerpc__)
	/*
	 * Enable the MSI mapping window for all HyperTransport
	 * slaves.  PCI-PCI bridges have their windows enabled via
	 * PCIB_MAP_MSI().
	 */
	if (cfg->ht.ht_slave != 0 && cfg->ht.ht_msimap != 0 &&
	    !(cfg->ht.ht_msictrl & PCIM_HTCMD_MSI_ENABLE)) {
		device_printf(pcib,
	    "Enabling MSI window for HyperTransport slave at pci%d:%d:%d:%d\n",
		    cfg->domain, cfg->bus, cfg->slot, cfg->func);
		 cfg->ht.ht_msictrl |= PCIM_HTCMD_MSI_ENABLE;
		 WREG(cfg->ht.ht_msimap + PCIR_HT_COMMAND, cfg->ht.ht_msictrl,
		     2);
	}
#endif
/* REG and WREG use carry through to next functions */
}