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
 int /*<<< orphan*/  ata_eh_autopsy (struct ata_port*) ; 
 int /*<<< orphan*/  ata_eh_finish (struct ata_port*) ; 
 int /*<<< orphan*/  ata_eh_report (struct ata_port*) ; 
 int /*<<< orphan*/  sata_pmp_eh_recover (struct ata_port*) ; 

void sata_pmp_error_handler(struct ata_port *ap)
{
	ata_eh_autopsy(ap);
	ata_eh_report(ap);
	sata_pmp_eh_recover(ap);
	ata_eh_finish(ap);
}