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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ I3200_CAPID0 ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,unsigned char*) ; 

__attribute__((used)) static int how_many_channels(struct pci_dev *pdev)
{
	int n_channels;

	unsigned char capid0_8b; /* 8th byte of CAPID0 */

	pci_read_config_byte(pdev, I3200_CAPID0 + 8, &capid0_8b);

	if (capid0_8b & 0x20) { /* check DCD: Dual Channel Disable */
		edac_dbg(0, "In single channel mode\n");
		n_channels = 1;
	} else {
		edac_dbg(0, "In dual channel mode\n");
		n_channels = 2;
	}

	if (capid0_8b & 0x10) /* check if both channels are filled */
		edac_dbg(0, "2 DIMMS per channel disabled\n");
	else
		edac_dbg(0, "2 DIMMS per channel enabled\n");

	return n_channels;
}