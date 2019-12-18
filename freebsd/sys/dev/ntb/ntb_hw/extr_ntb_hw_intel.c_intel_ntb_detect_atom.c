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
struct ntb_softc {int ppd; int conn_type; int /*<<< orphan*/  device; int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 int ATOM_PPD_CONN_TYPE ; 
 int ATOM_PPD_DEV_TYPE ; 
 int ENXIO ; 
#define  NTB_CONN_B2B 128 
 int /*<<< orphan*/  NTB_DEV_DSD ; 
 int /*<<< orphan*/  NTB_DEV_USD ; 
 int /*<<< orphan*/  NTB_PPD_OFFSET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
intel_ntb_detect_atom(struct ntb_softc *ntb)
{
	uint32_t ppd, conn_type;

	ppd = pci_read_config(ntb->device, NTB_PPD_OFFSET, 4);
	ntb->ppd = ppd;

	if ((ppd & ATOM_PPD_DEV_TYPE) != 0)
		ntb->dev_type = NTB_DEV_DSD;
	else
		ntb->dev_type = NTB_DEV_USD;

	conn_type = (ppd & ATOM_PPD_CONN_TYPE) >> 8;
	switch (conn_type) {
	case NTB_CONN_B2B:
		ntb->conn_type = conn_type;
		break;
	default:
		device_printf(ntb->device, "Unsupported NTB configuration\n");
		return (ENXIO);
	}
	return (0);
}