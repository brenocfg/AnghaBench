#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ ic_promisc; } ;
struct ural_softc {TYPE_1__ sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,char*) ; 
 int /*<<< orphan*/  RAL_DROP_NOT_TO_ME ; 
 int /*<<< orphan*/  RAL_TXRX_CSR2 ; 
 int /*<<< orphan*/  ural_read (struct ural_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ural_write (struct ural_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ural_setpromisc(struct ural_softc *sc)
{
	uint32_t tmp;

	tmp = ural_read(sc, RAL_TXRX_CSR2);

	tmp &= ~RAL_DROP_NOT_TO_ME;
	if (sc->sc_ic.ic_promisc == 0)
		tmp |= RAL_DROP_NOT_TO_ME;

	ural_write(sc, RAL_TXRX_CSR2, tmp);

	DPRINTF("%s promiscuous mode\n", sc->sc_ic.ic_promisc ?
	    "entering" : "leaving");
}