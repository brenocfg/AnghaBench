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
struct ata_queued_cmd {int dummy; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 unsigned int __ata_sff_port_intr (struct ata_port*,struct ata_queued_cmd*,int) ; 

unsigned int ata_sff_port_intr(struct ata_port *ap, struct ata_queued_cmd *qc)
{
	return __ata_sff_port_intr(ap, qc, false);
}