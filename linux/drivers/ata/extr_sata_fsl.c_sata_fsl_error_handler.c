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
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  sata_pmp_error_handler (struct ata_port*) ; 

__attribute__((used)) static void sata_fsl_error_handler(struct ata_port *ap)
{

	DPRINTK("in xx_error_handler\n");
	sata_pmp_error_handler(ap);

}