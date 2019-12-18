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
typedef  int /*<<< orphan*/  u_int ;
struct mc146818_softc {int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MC_ADDR ; 
 int /*<<< orphan*/  MC_DATA ; 
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mc146818_softc* device_get_softc (int /*<<< orphan*/ ) ; 

u_int
mc146818_def_read(device_t dev, u_int reg)
{
	struct mc146818_softc *sc;

	sc = device_get_softc(dev);
	bus_space_write_1(sc->sc_bst, sc->sc_bsh, MC_ADDR, reg);
	return (bus_space_read_1(sc->sc_bst, sc->sc_bsh, MC_DATA));
}