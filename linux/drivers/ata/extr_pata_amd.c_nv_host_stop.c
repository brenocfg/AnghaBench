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
typedef  unsigned long u32 ;
struct ata_host {int /*<<< orphan*/  dev; scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nv_host_stop(struct ata_host *host)
{
	u32 udma = (unsigned long)host->private_data;

	/* restore PCI config register 0x60 */
	pci_write_config_dword(to_pci_dev(host->dev), 0x60, udma);
}