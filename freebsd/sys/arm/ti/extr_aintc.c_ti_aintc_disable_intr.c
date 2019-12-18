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
struct ti_aintc_softc {int dummy; } ;
struct ti_aintc_irqsrc {int /*<<< orphan*/  tai_irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ti_aintc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_aintc_irq_mask (struct ti_aintc_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ti_aintc_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	u_int irq = ((struct ti_aintc_irqsrc *)isrc)->tai_irq;
	struct ti_aintc_softc *sc = device_get_softc(dev);

	ti_aintc_irq_mask(sc, irq);
}