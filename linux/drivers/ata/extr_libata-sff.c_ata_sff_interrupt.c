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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ata_sff_interrupt (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sff_port_intr ; 

irqreturn_t ata_sff_interrupt(int irq, void *dev_instance)
{
	return __ata_sff_interrupt(irq, dev_instance, ata_sff_port_intr);
}