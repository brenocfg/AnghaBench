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
typedef  scalar_t__ uint32_t ;
struct tsec_softc {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int OF_getprop (int /*<<< orphan*/ ,char*,void*,int) ; 
 void* TSEC_READ (struct tsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSEC_REG_MACSTNADDR1 ; 
 int /*<<< orphan*/  TSEC_REG_MACSTNADDR2 ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
tsec_get_hwaddr(struct tsec_softc *sc, uint8_t *addr)
{
	union {
		uint32_t reg[2];
		uint8_t addr[6];
	} hw;
	int i;

	hw.reg[0] = hw.reg[1] = 0;

	/* Retrieve the hardware address from the device tree. */
	i = OF_getprop(sc->node, "local-mac-address", (void *)hw.addr, 6);
	if (i == 6 && (hw.reg[0] != 0 || hw.reg[1] != 0)) {
		bcopy(hw.addr, addr, 6);
		return;
	}

	/* Also try the mac-address property, which is second-best */
	i = OF_getprop(sc->node, "mac-address", (void *)hw.addr, 6);
	if (i == 6 && (hw.reg[0] != 0 || hw.reg[1] != 0)) {
		bcopy(hw.addr, addr, 6);
		return;
	}

	/*
	 * Fall back -- use the currently programmed address in the hope that
	 * it was set be firmware...
	 */
	hw.reg[0] = TSEC_READ(sc, TSEC_REG_MACSTNADDR1);
	hw.reg[1] = TSEC_READ(sc, TSEC_REG_MACSTNADDR2);
	for (i = 0; i < 6; i++)
		addr[5-i] = hw.addr[i];
}