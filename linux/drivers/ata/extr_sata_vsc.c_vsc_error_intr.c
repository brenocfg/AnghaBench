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
typedef  int u8 ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int VSC_SATA_INT_ERROR_M ; 
 int VSC_SATA_INT_PHY_CHANGE ; 
 int /*<<< orphan*/  ata_port_abort (struct ata_port*) ; 
 int /*<<< orphan*/  ata_port_freeze (struct ata_port*) ; 

__attribute__((used)) static inline void vsc_error_intr(u8 port_status, struct ata_port *ap)
{
	if (port_status & (VSC_SATA_INT_PHY_CHANGE | VSC_SATA_INT_ERROR_M))
		ata_port_freeze(ap);
	else
		ata_port_abort(ap);
}