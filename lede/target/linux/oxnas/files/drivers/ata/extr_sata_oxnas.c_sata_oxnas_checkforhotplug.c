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
struct TYPE_2__ {int /*<<< orphan*/  eh_info; } ;
struct ata_port {TYPE_1__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  ata_ehi_hotplugged (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ata_port_freeze (struct ata_port*) ; 

void sata_oxnas_checkforhotplug(struct ata_port *ap)
{
	DPRINTK("ENTER\n");

	ata_ehi_hotplugged(&ap->link.eh_info);
	ata_port_freeze(ap);
}