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
struct ntb_softc {int ppd; int conn_type; int /*<<< orphan*/  device; int /*<<< orphan*/  features; int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
#define  NTB_CONN_B2B 130 
#define  NTB_CONN_RP 129 
#define  NTB_CONN_TRANSPARENT 128 
 int /*<<< orphan*/  NTB_DEV_DSD ; 
 int /*<<< orphan*/  NTB_DEV_USD ; 
 int /*<<< orphan*/  NTB_PPD_OFFSET ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 int /*<<< orphan*/  NTB_SDOORBELL_LOCKUP ; 
 int /*<<< orphan*/  NTB_SPLIT_BAR ; 
 int XEON_PPD_CONN_TYPE ; 
 int XEON_PPD_DEV_TYPE ; 
 int XEON_PPD_SPLIT_BAR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
intel_ntb_detect_xeon(struct ntb_softc *ntb)
{
	uint8_t ppd, conn_type;

	ppd = pci_read_config(ntb->device, NTB_PPD_OFFSET, 1);
	ntb->ppd = ppd;

	if ((ppd & XEON_PPD_DEV_TYPE) != 0)
		ntb->dev_type = NTB_DEV_DSD;
	else
		ntb->dev_type = NTB_DEV_USD;

	if ((ppd & XEON_PPD_SPLIT_BAR) != 0)
		ntb->features |= NTB_SPLIT_BAR;

	if (HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP) &&
	    !HAS_FEATURE(ntb, NTB_SPLIT_BAR)) {
		device_printf(ntb->device,
		    "Can not apply SB01BASE_LOCKUP workaround "
		    "with split BARs disabled!\n");
		device_printf(ntb->device,
		    "Expect system hangs under heavy NTB traffic!\n");
		ntb->features &= ~NTB_SB01BASE_LOCKUP;
	}

	/*
	 * SDOORBELL errata workaround gets in the way of SB01BASE_LOCKUP
	 * errata workaround; only do one at a time.
	 */
	if (HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP))
		ntb->features &= ~NTB_SDOORBELL_LOCKUP;

	conn_type = ppd & XEON_PPD_CONN_TYPE;
	switch (conn_type) {
	case NTB_CONN_B2B:
		ntb->conn_type = conn_type;
		break;
	case NTB_CONN_RP:
	case NTB_CONN_TRANSPARENT:
	default:
		device_printf(ntb->device, "Unsupported connection type: %u\n",
		    (unsigned)conn_type);
		return (ENXIO);
	}
	return (0);
}