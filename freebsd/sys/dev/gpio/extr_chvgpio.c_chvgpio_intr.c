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
typedef  int uint32_t ;
struct chvgpio_softc {int /*<<< orphan*/  sc_mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHVGPIO_INTERRUPT_STATUS ; 
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
chvgpio_intr(void *arg)
{
	struct chvgpio_softc *sc = arg;
	uint32_t reg;
	int line;

	reg = bus_read_4(sc->sc_mem_res, CHVGPIO_INTERRUPT_STATUS);
	for (line = 0; line < 16; line++) {
		if ((reg & (1 << line)) == 0)
			continue;
		bus_write_4(sc->sc_mem_res, CHVGPIO_INTERRUPT_STATUS, 1 << line);
	}
}