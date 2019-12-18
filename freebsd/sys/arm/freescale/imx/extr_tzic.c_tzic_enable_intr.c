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
struct tzic_softc {int dummy; } ;
struct tzic_irqsrc {int /*<<< orphan*/  irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 
 struct tzic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tzic_irq_unmask (struct tzic_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tzic_enable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	u_int irq = ((struct tzic_irqsrc *)isrc)->irq;
	struct tzic_softc *sc = device_get_softc(dev);

	arm_irq_memory_barrier(irq);
	tzic_irq_unmask(sc, irq);
}