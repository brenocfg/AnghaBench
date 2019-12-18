#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ata_link {TYPE_1__* ap; } ;
struct TYPE_2__ {int port_no; } ;

/* Variables and functions */
 scalar_t__ ali_isa_bridge ; 
 int /*<<< orphan*/  ata_sff_postreset (struct ata_link*,unsigned int*) ; 
 int /*<<< orphan*/  pci_read_config_byte (scalar_t__,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (scalar_t__,int,int) ; 

__attribute__((used)) static void ali_c2_c3_postreset(struct ata_link *link, unsigned int *classes)
{
	u8 r;
	int port_bit = 4 << link->ap->port_no;

	/* If our bridge is an ALI 1533 then do the extra work */
	if (ali_isa_bridge) {
		/* Tristate and re-enable the bus signals */
		pci_read_config_byte(ali_isa_bridge, 0x58, &r);
		r &= ~port_bit;
		pci_write_config_byte(ali_isa_bridge, 0x58, r);
		r |= port_bit;
		pci_write_config_byte(ali_isa_bridge, 0x58, r);
	}
	ata_sff_postreset(link, classes);
}