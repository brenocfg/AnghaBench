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
typedef  int u32 ;
struct sata_oxnas_port_priv {scalar_t__ core_base; scalar_t__ port_base; } ;
struct ata_port {int port_no; struct sata_oxnas_port_priv* private_data; } ;

/* Variables and functions */
 int COREINT_END ; 
 scalar_t__ CORE_INT_ENABLE ; 
 scalar_t__ CORE_INT_STATUS ; 
 scalar_t__ INT_CLEAR ; 
 scalar_t__ INT_ENABLE ; 
 int INT_WANT ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sata_oxnas_irq_on(struct ata_port *ap)
{
	struct sata_oxnas_port_priv *pd = ap->private_data;
	u32 mask = (COREINT_END << ap->port_no);

	/* Clear pending interrupts */
	iowrite32(~0, pd->port_base + INT_CLEAR);
	iowrite32(mask, pd->core_base + CORE_INT_STATUS);
	wmb();

	/* enable End of command interrupt */
	iowrite32(INT_WANT, pd->port_base + INT_ENABLE);
	iowrite32(mask, pd->core_base + CORE_INT_ENABLE);
}