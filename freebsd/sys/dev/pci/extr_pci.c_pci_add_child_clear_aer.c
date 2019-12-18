#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {scalar_t__ pcie_location; scalar_t__ pcie_type; } ;
struct TYPE_4__ {TYPE_1__ pcie; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIEM_CTL_COR_ENABLE ; 
 int PCIEM_CTL_FER_ENABLE ; 
 int PCIEM_CTL_NFER_ENABLE ; 
 int PCIEM_CTL_URR_ENABLE ; 
 int PCIEM_ROOT_CTL_SERR_CORR ; 
 int PCIEM_ROOT_CTL_SERR_FATAL ; 
 int PCIEM_ROOT_CTL_SERR_NONFATAL ; 
 scalar_t__ PCIEM_TYPE_ROOT_PORT ; 
 scalar_t__ PCIER_DEVICE_CTL ; 
 scalar_t__ PCIER_ROOT_CTL ; 
 int PCIM_AER_COR_ADVISORY_NF_ERROR ; 
 int PCIM_AER_COR_BAD_DLLP ; 
 int PCIM_AER_COR_BAD_TLP ; 
 int PCIM_AER_COR_HEADER_LOG_OVFLOW ; 
 int PCIM_AER_COR_INTERNAL_ERROR ; 
 int PCIM_AER_COR_RECEIVER_ERROR ; 
 int PCIM_AER_COR_REPLAY_ROLLOVER ; 
 int PCIM_AER_COR_REPLAY_TIMEOUT ; 
 int PCIM_AER_UC_ACS_VIOLATION ; 
 int PCIM_AER_UC_ATOMIC_EGRESS_BLK ; 
 int PCIM_AER_UC_COMPLETER_ABORT ; 
 int PCIM_AER_UC_COMPLETION_TIMEOUT ; 
 int PCIM_AER_UC_DL_PROTOCOL_ERROR ; 
 int PCIM_AER_UC_ECRC_ERROR ; 
 int PCIM_AER_UC_FC_PROTOCOL_ERROR ; 
 int PCIM_AER_UC_INTERNAL_ERROR ; 
 int PCIM_AER_UC_MALFORMED_TLP ; 
 int PCIM_AER_UC_MC_BLOCKED_TLP ; 
 int PCIM_AER_UC_POISONED_TLP ; 
 int PCIM_AER_UC_RECEIVER_OVERFLOW ; 
 int PCIM_AER_UC_SURPRISE_LINK_DOWN ; 
 int PCIM_AER_UC_TLP_PREFIX_BLOCKED ; 
 int PCIM_AER_UC_TRAINING_ERROR ; 
 int PCIM_AER_UC_UNEXPECTED_COMPLETION ; 
 int PCIM_AER_UC_UNSUPPORTED_REQUEST ; 
 scalar_t__ PCIR_AER_COR_MASK ; 
 scalar_t__ PCIR_AER_COR_STATUS ; 
 scalar_t__ PCIR_AER_UC_MASK ; 
 scalar_t__ PCIR_AER_UC_STATUS ; 
 int /*<<< orphan*/  PCIZ_AER ; 
 scalar_t__ bootverbose ; 
 scalar_t__ pci_find_extcap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_printf (TYPE_2__*,char*,int,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
pci_add_child_clear_aer(device_t dev, struct pci_devinfo *dinfo)
{
	int aer;
	uint32_t r;
	uint16_t r2;

	if (dinfo->cfg.pcie.pcie_location != 0 &&
	    dinfo->cfg.pcie.pcie_type == PCIEM_TYPE_ROOT_PORT) {
		r2 = pci_read_config(dev, dinfo->cfg.pcie.pcie_location +
		    PCIER_ROOT_CTL, 2);
		r2 &= ~(PCIEM_ROOT_CTL_SERR_CORR |
		    PCIEM_ROOT_CTL_SERR_NONFATAL | PCIEM_ROOT_CTL_SERR_FATAL);
		pci_write_config(dev, dinfo->cfg.pcie.pcie_location +
		    PCIER_ROOT_CTL, r2, 2);
	}
	if (pci_find_extcap(dev, PCIZ_AER, &aer) == 0) {
		r = pci_read_config(dev, aer + PCIR_AER_UC_STATUS, 4);
		pci_write_config(dev, aer + PCIR_AER_UC_STATUS, r, 4);
		if (r != 0 && bootverbose) {
			pci_printf(&dinfo->cfg,
			    "clearing AER UC 0x%08x -> 0x%08x\n",
			    r, pci_read_config(dev, aer + PCIR_AER_UC_STATUS,
			    4));
		}

		r = pci_read_config(dev, aer + PCIR_AER_UC_MASK, 4);
		r &= ~(PCIM_AER_UC_TRAINING_ERROR |
		    PCIM_AER_UC_DL_PROTOCOL_ERROR |
		    PCIM_AER_UC_SURPRISE_LINK_DOWN |
		    PCIM_AER_UC_POISONED_TLP |
		    PCIM_AER_UC_FC_PROTOCOL_ERROR |
		    PCIM_AER_UC_COMPLETION_TIMEOUT |
		    PCIM_AER_UC_COMPLETER_ABORT |
		    PCIM_AER_UC_UNEXPECTED_COMPLETION |
		    PCIM_AER_UC_RECEIVER_OVERFLOW |
		    PCIM_AER_UC_MALFORMED_TLP |
		    PCIM_AER_UC_ECRC_ERROR |
		    PCIM_AER_UC_UNSUPPORTED_REQUEST |
		    PCIM_AER_UC_ACS_VIOLATION |
		    PCIM_AER_UC_INTERNAL_ERROR |
		    PCIM_AER_UC_MC_BLOCKED_TLP |
		    PCIM_AER_UC_ATOMIC_EGRESS_BLK |
		    PCIM_AER_UC_TLP_PREFIX_BLOCKED);
		pci_write_config(dev, aer + PCIR_AER_UC_MASK, r, 4);

		r = pci_read_config(dev, aer + PCIR_AER_COR_STATUS, 4);
		pci_write_config(dev, aer + PCIR_AER_COR_STATUS, r, 4);
		if (r != 0 && bootverbose) {
			pci_printf(&dinfo->cfg,
			    "clearing AER COR 0x%08x -> 0x%08x\n",
			    r, pci_read_config(dev, aer + PCIR_AER_COR_STATUS,
			    4));
		}

		r = pci_read_config(dev, aer + PCIR_AER_COR_MASK, 4);
		r &= ~(PCIM_AER_COR_RECEIVER_ERROR |
		    PCIM_AER_COR_BAD_TLP |
		    PCIM_AER_COR_BAD_DLLP |
		    PCIM_AER_COR_REPLAY_ROLLOVER |
		    PCIM_AER_COR_REPLAY_TIMEOUT |
		    PCIM_AER_COR_ADVISORY_NF_ERROR |
		    PCIM_AER_COR_INTERNAL_ERROR |
		    PCIM_AER_COR_HEADER_LOG_OVFLOW);
		pci_write_config(dev, aer + PCIR_AER_COR_MASK, r, 4);

		r = pci_read_config(dev, dinfo->cfg.pcie.pcie_location +
		    PCIER_DEVICE_CTL, 2);
		r |=  PCIEM_CTL_COR_ENABLE | PCIEM_CTL_NFER_ENABLE |
		    PCIEM_CTL_FER_ENABLE | PCIEM_CTL_URR_ENABLE;
		pci_write_config(dev, dinfo->cfg.pcie.pcie_location +
		    PCIER_DEVICE_CTL, r, 2);
	}
}