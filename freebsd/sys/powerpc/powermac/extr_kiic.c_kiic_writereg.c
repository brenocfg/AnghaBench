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
typedef  int u_int ;
struct kiic_softc {int sc_regstep; int /*<<< orphan*/  sc_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
kiic_writereg(struct kiic_softc *sc, u_int reg, u_int val)
{
	bus_write_4(sc->sc_reg, sc->sc_regstep * reg, val);
	DELAY(100); /* register access delay */
}