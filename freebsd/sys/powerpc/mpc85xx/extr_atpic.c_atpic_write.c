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
typedef  int /*<<< orphan*/  uint8_t ;
struct atpic_softc {int /*<<< orphan*/ * sc_res; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
atpic_write(struct atpic_softc *sc, int icu, int ofs, uint8_t val)
{

	bus_write_1(sc->sc_res[icu], ofs, val);
	bus_barrier(sc->sc_res[icu], ofs, 2 - ofs,
	    BUS_SPACE_BARRIER_READ|BUS_SPACE_BARRIER_WRITE);
}