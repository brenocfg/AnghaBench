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
struct as3722_softc {scalar_t__ i2c_pullup; scalar_t__ int_pullup; } ;

/* Variables and functions */
 int AS3722_I2C_PULL_UP ; 
 int /*<<< orphan*/  AS3722_INTERRUPT_MASK1 ; 
 int /*<<< orphan*/  AS3722_INTERRUPT_MASK2 ; 
 int /*<<< orphan*/  AS3722_INTERRUPT_MASK3 ; 
 int /*<<< orphan*/  AS3722_INTERRUPT_MASK4 ; 
 int AS3722_INT_PULL_UP ; 
 int /*<<< orphan*/  AS3722_IO_VOLTAGE ; 
 int ENXIO ; 
 int RM1 (struct as3722_softc*,int /*<<< orphan*/ ,int,int) ; 
 int WR1 (struct as3722_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
as3722_init(struct as3722_softc *sc)
{
	uint32_t reg;
	int rv;

	reg = 0;
	if (sc->int_pullup)
		reg |= AS3722_INT_PULL_UP;
	if (sc->i2c_pullup)
		reg |= AS3722_I2C_PULL_UP;

	rv = RM1(sc, AS3722_IO_VOLTAGE,
	    AS3722_INT_PULL_UP | AS3722_I2C_PULL_UP, reg);
	if (rv != 0)
		return (ENXIO);

	/* mask interrupts */
	rv = WR1(sc, AS3722_INTERRUPT_MASK1, 0);
	if (rv != 0)
		return (ENXIO);
	rv = WR1(sc, AS3722_INTERRUPT_MASK2, 0);
	if (rv != 0)
		return (ENXIO);
	rv = WR1(sc, AS3722_INTERRUPT_MASK3, 0);
	if (rv != 0)
		return (ENXIO);
	rv = WR1(sc, AS3722_INTERRUPT_MASK4, 0);
	if (rv != 0)
		return (ENXIO);
	return (0);
}