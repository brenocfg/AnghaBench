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
struct ata_port {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  z_writeb (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pata_xsurf_irq_clear(struct ata_port *ap)
{
	z_writeb(0, (unsigned long)ap->private_data);
}