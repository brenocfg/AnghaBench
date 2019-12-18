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
struct gicv3_its_softc {scalar_t__ sc_irq_base; } ;
struct gicv3_its_irqsrc {scalar_t__ gi_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOIR1 ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_icc_write (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
gicv3_its_post_filter(device_t dev, struct intr_irqsrc *isrc)
{
	struct gicv3_its_irqsrc *girq;
	struct gicv3_its_softc *sc;

	sc = device_get_softc(dev);
	girq = (struct gicv3_its_irqsrc *)isrc;
	gic_icc_write(EOIR1, girq->gi_irq + sc->sc_irq_base);
}