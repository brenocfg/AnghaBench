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
struct pl190_intc_softc {int dummy; } ;
struct pl190_intc_irqsrc {int irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTC_VIC_WRITE_4 (struct pl190_intc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VICINTENABLE ; 
 int /*<<< orphan*/  VIC_LOCK (struct pl190_intc_softc*) ; 
 int /*<<< orphan*/  VIC_UNLOCK (struct pl190_intc_softc*) ; 
 struct pl190_intc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pl190_intc_enable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct pl190_intc_softc *sc;
	struct pl190_intc_irqsrc *src;

	sc = device_get_softc(dev);
	src = (struct pl190_intc_irqsrc *)isrc;

	VIC_LOCK(sc);
	INTC_VIC_WRITE_4(sc, VICINTENABLE, (1 << src->irq));
	VIC_UNLOCK(sc);
}