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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct unin_chip_softc {scalar_t__ sc_addr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct unin_chip_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ inl (int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/  volatile*,scalar_t__) ; 

__attribute__((used)) static void
unin_update_reg(device_t dev, uint32_t regoff, uint32_t set, uint32_t clr)
{
	volatile u_int *reg;
	struct unin_chip_softc *sc;
	u_int32_t tmpl;

	sc = device_get_softc(dev);
	reg = (void *)(sc->sc_addr + regoff);
	tmpl = inl(reg);
	tmpl &= ~clr;
	tmpl |= set;
	outl(reg, tmpl);
}