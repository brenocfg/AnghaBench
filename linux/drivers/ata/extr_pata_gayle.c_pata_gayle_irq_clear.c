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
struct TYPE_2__ {scalar_t__ status_addr; } ;
struct ata_port {scalar_t__ private_data; TYPE_1__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  z_readb (unsigned long) ; 
 int /*<<< orphan*/  z_writeb (int,unsigned long) ; 

__attribute__((used)) static void pata_gayle_irq_clear(struct ata_port *ap)
{
	(void)z_readb((unsigned long)ap->ioaddr.status_addr);
	z_writeb(0x7c, (unsigned long)ap->private_data);
}