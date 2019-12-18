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
struct sata_oxnas_port_priv {scalar_t__ core_base; scalar_t__ port_base; } ;
struct ata_port {struct sata_oxnas_port_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  COREINT_END ; 
 scalar_t__ CORE_INT_CLEAR ; 
 scalar_t__ INT_CLEAR ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sata_oxnas_irq_clear(struct ata_port *ap)
{
	struct sata_oxnas_port_priv *port_priv = ap->private_data;

	/* clear pending interrupts */
	iowrite32(~0, port_priv->port_base + INT_CLEAR);
	iowrite32(COREINT_END, port_priv->core_base + CORE_INT_CLEAR);
}