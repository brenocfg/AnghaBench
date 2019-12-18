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
struct plic_softc {int dummy; } ;
struct plic_irqsrc {int /*<<< orphan*/  irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PLIC_PRIORITY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct plic_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct plic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
plic_disable_intr(device_t dev, struct intr_irqsrc *isrc)
{
	struct plic_softc *sc;
	struct plic_irqsrc *src;

	sc = device_get_softc(dev);
	src = (struct plic_irqsrc *)isrc;

	WR4(sc, PLIC_PRIORITY(src->irq), 0);
}