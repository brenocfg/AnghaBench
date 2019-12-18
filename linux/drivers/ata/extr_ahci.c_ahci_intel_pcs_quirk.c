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
typedef  int u16 ;
struct pci_device_id {scalar_t__ vendor; scalar_t__ driver_data; } ;
struct pci_dev {int dummy; } ;
struct ahci_host_priv {int port_map; } ;
typedef  enum board_ids { ____Placeholder_board_ids } board_ids ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  PCS_6 ; 
 int /*<<< orphan*/  ahci_pci_tbl ; 
 int board_ahci_pcs7 ; 
 struct pci_device_id* pci_match_id (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ahci_intel_pcs_quirk(struct pci_dev *pdev, struct ahci_host_priv *hpriv)
{
	const struct pci_device_id *id = pci_match_id(ahci_pci_tbl, pdev);
	u16 tmp16;

	/*
	 * Only apply the 6-port PCS quirk for known legacy platforms.
	 */
	if (!id || id->vendor != PCI_VENDOR_ID_INTEL)
		return;

	/* Skip applying the quirk on Denverton and beyond */
	if (((enum board_ids) id->driver_data) >= board_ahci_pcs7)
		return;

	/*
	 * port_map is determined from PORTS_IMPL PCI register which is
	 * implemented as write or write-once register.  If the register
	 * isn't programmed, ahci automatically generates it from number
	 * of ports, which is good enough for PCS programming. It is
	 * otherwise expected that platform firmware enables the ports
	 * before the OS boots.
	 */
	pci_read_config_word(pdev, PCS_6, &tmp16);
	if ((tmp16 & hpriv->port_map) != hpriv->port_map) {
		tmp16 |= hpriv->port_map;
		pci_write_config_word(pdev, PCS_6, tmp16);
	}
}