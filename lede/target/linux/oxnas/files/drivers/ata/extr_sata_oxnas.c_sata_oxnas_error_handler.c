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
struct ata_port {int /*<<< orphan*/  host; int /*<<< orphan*/  port_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_std_error_handler (struct ata_port*) ; 
 int /*<<< orphan*/  sata_oxnas_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_oxnas_freeze_host (struct ata_port*) ; 
 int /*<<< orphan*/  sata_oxnas_thaw_host (struct ata_port*) ; 

__attribute__((used)) static void sata_oxnas_error_handler(struct ata_port *ap)
{
	DPRINTK("Enter port_no %d\n", ap->port_no);
	sata_oxnas_freeze_host(ap);

	/* If the core is busy here, make it idle */
	sata_oxnas_cleanup(ap->host);

	ata_std_error_handler(ap);

	sata_oxnas_thaw_host(ap);
}