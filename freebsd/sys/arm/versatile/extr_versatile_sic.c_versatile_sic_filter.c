#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct versatile_sic_softc {int /*<<< orphan*/  dev; TYPE_1__* isrcs; } ;
struct intr_irqsrc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_3__ {struct intr_irqsrc isrc; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  SIC_LOCK (struct versatile_sic_softc*) ; 
 int SIC_READ_4 (struct versatile_sic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIC_STATUS ; 
 int /*<<< orphan*/  SIC_UNLOCK (struct versatile_sic_softc*) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ intr_isrc_dispatch (struct intr_irqsrc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  versatile_sic_disable_intr (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 int /*<<< orphan*/  versatile_sic_post_filter (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 

__attribute__((used)) static int
versatile_sic_filter(void *arg)
{
	struct versatile_sic_softc *sc;
	struct intr_irqsrc *isrc;
	uint32_t i, interrupts;

	sc = arg;
	SIC_LOCK(sc);
	interrupts = SIC_READ_4(sc, SIC_STATUS);
	SIC_UNLOCK(sc);
	for (i = 0; interrupts != 0; i++, interrupts >>= 1) {
		if ((interrupts & 0x1) == 0)
			continue;
		isrc = &sc->isrcs[i].isrc;
		if (intr_isrc_dispatch(isrc, curthread->td_intr_frame) != 0) {
			versatile_sic_disable_intr(sc->dev, isrc);
			versatile_sic_post_filter(sc->dev, isrc);
			device_printf(sc->dev, "Stray irq %u disabled\n", i);
		}
	}

	return (FILTER_HANDLED);
}