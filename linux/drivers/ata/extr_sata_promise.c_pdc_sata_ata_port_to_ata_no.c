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
struct ata_port {int /*<<< orphan*/  flags; struct ata_host* host; } ;
struct ata_host {struct ata_port const** ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  pdc_is_sataii_tx4 (int /*<<< orphan*/ ) ; 
 unsigned int pdc_port_no_to_ata_no (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int pdc_sata_nr_ports (struct ata_port const*) ; 

__attribute__((used)) static unsigned int pdc_sata_ata_port_to_ata_no(const struct ata_port *ap)
{
	const struct ata_host *host = ap->host;
	unsigned int nr_ports = pdc_sata_nr_ports(ap);
	unsigned int i;

	for (i = 0; i < nr_ports && host->ports[i] != ap; ++i)
		;
	BUG_ON(i >= nr_ports);
	return pdc_port_no_to_ata_no(i, pdc_is_sataii_tx4(ap->flags));
}