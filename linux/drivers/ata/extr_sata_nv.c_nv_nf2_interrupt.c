#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ata_host {int /*<<< orphan*/  lock; TYPE_2__** ports; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ scr_addr; } ;
struct TYPE_4__ {TYPE_1__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ NV_INT_STATUS ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  nv_do_interrupt (struct ata_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nv_nf2_interrupt(int irq, void *dev_instance)
{
	struct ata_host *host = dev_instance;
	u8 irq_stat;
	irqreturn_t ret;

	spin_lock(&host->lock);
	irq_stat = ioread8(host->ports[0]->ioaddr.scr_addr + NV_INT_STATUS);
	ret = nv_do_interrupt(host, irq_stat);
	spin_unlock(&host->lock);

	return ret;
}