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
 int /*<<< orphan*/  SCR_STATUS ; 
 int /*<<< orphan*/  sata_oxnas_scr_read_port (struct ata_port*,int /*<<< orphan*/ ,int*) ; 

int sata_oxnas_check_link(struct ata_port *ap)
{
	int reg;

	sata_oxnas_scr_read_port(ap, SCR_STATUS, &reg);
	/* Check for the cable present indicated by SCR status bit-0 set */
	return reg & 0x1;
}