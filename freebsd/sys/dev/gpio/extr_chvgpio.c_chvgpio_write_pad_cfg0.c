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
typedef  int /*<<< orphan*/  uint32_t ;
struct chvgpio_softc {int /*<<< orphan*/  sc_mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chvgpio_pad_cfg0_offset (int) ; 

__attribute__((used)) static inline void
chvgpio_write_pad_cfg0(struct chvgpio_softc *sc, int pin, uint32_t val)
{
	bus_write_4(sc->sc_mem_res, chvgpio_pad_cfg0_offset(pin), val);
}