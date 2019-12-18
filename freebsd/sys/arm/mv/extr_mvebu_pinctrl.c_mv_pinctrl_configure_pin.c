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
struct mv_pinctrl_softc {int dummy; } ;

/* Variables and functions */
 int BITS_PER_PIN ; 
 int PINS_MASK ; 
 int PINS_PER_REG ; 
 int RD4 (struct mv_pinctrl_softc*,int) ; 
 int /*<<< orphan*/  WR4 (struct mv_pinctrl_softc*,int,int) ; 

__attribute__((used)) static void
mv_pinctrl_configure_pin(struct mv_pinctrl_softc *sc, uint32_t pin,
    uint32_t function)
{
	uint32_t offset, shift, reg;

	offset = (pin / PINS_PER_REG) * BITS_PER_PIN;
	shift = (pin % PINS_PER_REG) * BITS_PER_PIN;
	reg = RD4(sc, offset);
	reg &= ~(PINS_MASK << shift);
	reg |= function << shift;
	WR4(sc, offset, reg);
}