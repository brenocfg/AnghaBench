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
struct chvgpio_softc {int /*<<< orphan*/  sc_mem_res; } ;

/* Variables and functions */
 int bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chvgpio_pad_cfg0_offset (int) ; 

__attribute__((used)) static inline int
chvgpio_read_pad_cfg0(struct chvgpio_softc *sc, int pin)
{
	return bus_read_4(sc->sc_mem_res, chvgpio_pad_cfg0_offset(pin));
}