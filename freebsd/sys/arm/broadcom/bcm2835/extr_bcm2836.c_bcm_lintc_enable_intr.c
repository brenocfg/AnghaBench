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
struct intr_irqsrc {int dummy; } ;
struct bcm_lintc_irqsrc {int /*<<< orphan*/  bli_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_lintc_unmask (int /*<<< orphan*/ ,struct bcm_lintc_irqsrc*) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_lintc_enable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct bcm_lintc_irqsrc *bli = (struct bcm_lintc_irqsrc *)isrc;

	arm_irq_memory_barrier(bli->bli_irq);
	bcm_lintc_unmask(device_get_softc(dev), bli);
}