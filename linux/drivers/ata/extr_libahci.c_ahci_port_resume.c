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
struct ata_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahci_pmp_attach (struct ata_port*) ; 
 int /*<<< orphan*/  ahci_pmp_detach (struct ata_port*) ; 
 int /*<<< orphan*/  ahci_power_up (struct ata_port*) ; 
 int /*<<< orphan*/  ahci_rpm_get_port (struct ata_port*) ; 
 int /*<<< orphan*/  ahci_start_port (struct ata_port*) ; 
 scalar_t__ sata_pmp_attached (struct ata_port*) ; 

int ahci_port_resume(struct ata_port *ap)
{
	ahci_rpm_get_port(ap);

	ahci_power_up(ap);
	ahci_start_port(ap);

	if (sata_pmp_attached(ap))
		ahci_pmp_attach(ap);
	else
		ahci_pmp_detach(ap);

	return 0;
}