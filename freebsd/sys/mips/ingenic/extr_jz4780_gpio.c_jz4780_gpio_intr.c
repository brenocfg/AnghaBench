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
struct jz4780_gpio_softc {TYPE_1__* pins; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_intr_frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  pin_irqsrc; } ;

/* Variables and functions */
 int CSR_READ_4 (struct jz4780_gpio_softc*,int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  JZ_GPIO_FLAG ; 
 int /*<<< orphan*/  PIC_DISABLE_INTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ intr_isrc_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_gpio_intr(void *arg)
{
	struct jz4780_gpio_softc *sc;
	uint32_t i, interrupts;

	sc = arg;
	interrupts = CSR_READ_4(sc, JZ_GPIO_FLAG);

	for (i = 0; interrupts != 0; i++, interrupts >>= 1) {
		if ((interrupts & 0x1) == 0)
			continue;
		if (intr_isrc_dispatch(&sc->pins[i].pin_irqsrc,
		    curthread->td_intr_frame) != 0) {
			device_printf(sc->dev, "spurious interrupt %d\n", i);
			PIC_DISABLE_INTR(sc->dev, &sc->pins[i].pin_irqsrc);
		}
	}

	return (FILTER_HANDLED);
}