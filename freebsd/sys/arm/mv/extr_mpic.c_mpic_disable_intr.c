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
typedef  int /*<<< orphan*/  u_int ;
struct mv_mpic_irqsrc {int /*<<< orphan*/  mmi_irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  mpic_mask_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpic_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	u_int irq;

	irq = ((struct mv_mpic_irqsrc *)isrc)->mmi_irq;
	mpic_mask_irq(irq);
}