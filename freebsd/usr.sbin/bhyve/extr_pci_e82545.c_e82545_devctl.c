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
struct e82545_softc {int esc_CTRL; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int E1000_CTRL_RST ; 
 int /*<<< orphan*/  e82545_reset (struct e82545_softc*,int) ; 

__attribute__((used)) static void
e82545_devctl(struct e82545_softc *sc, uint32_t val)
{

	sc->esc_CTRL = val & ~E1000_CTRL_RST;

	if (val & E1000_CTRL_RST) {
		DPRINTF("e1k: s/w reset, ctl %x\n", val);
		e82545_reset(sc, 1);
	}
	/* XXX check for phy reset ? */
}