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
struct versatile_sic_softc {int dummy; } ;
struct versatile_sic_irqsrc {int irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIC_ENCLR ; 
 int /*<<< orphan*/  SIC_LOCK (struct versatile_sic_softc*) ; 
 int /*<<< orphan*/  SIC_UNLOCK (struct versatile_sic_softc*) ; 
 int /*<<< orphan*/  SIC_WRITE_4 (struct versatile_sic_softc*,int /*<<< orphan*/ ,int) ; 
 struct versatile_sic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
versatile_sic_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct versatile_sic_softc *sc;
	struct versatile_sic_irqsrc *src;

	sc = device_get_softc(dev);
	src = (struct versatile_sic_irqsrc *)isrc;

	SIC_LOCK(sc);
	SIC_WRITE_4(sc, SIC_ENCLR, (1 << src->irq));
	SIC_UNLOCK(sc);
}