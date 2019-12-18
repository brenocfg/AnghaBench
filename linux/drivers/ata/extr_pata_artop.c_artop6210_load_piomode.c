#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; int member_4; } ;
typedef  TYPE_2__ u16 ;
struct pci_dev {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* host; } ;
struct ata_device {int devno; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t clock ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,TYPE_2__ const) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void artop6210_load_piomode(struct ata_port *ap, struct ata_device *adev, unsigned int pio)
{
	struct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int dn = adev->devno + 2 * ap->port_no;
	const u16 timing[2][5] = {
		{ 0x0000, 0x000A, 0x0008, 0x0303, 0x0301 },
		{ 0x0700, 0x070A, 0x0708, 0x0403, 0x0401 }

	};
	/* Load the PIO timing active/recovery bits */
	pci_write_config_word(pdev, 0x40 + 2 * dn, timing[clock][pio]);
}