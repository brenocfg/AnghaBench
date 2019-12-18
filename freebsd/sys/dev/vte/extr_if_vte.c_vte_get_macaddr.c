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
typedef  int uint16_t ;
struct vte_softc {int* vte_eaddr; } ;

/* Variables and functions */
 int CSR_READ_2 (struct vte_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTE_MID0H ; 
 int /*<<< orphan*/  VTE_MID0L ; 
 int /*<<< orphan*/  VTE_MID0M ; 

__attribute__((used)) static void
vte_get_macaddr(struct vte_softc *sc)
{
	uint16_t mid;

	/*
	 * It seems there is no way to reload station address and
	 * it is supposed to be set by BIOS.
	 */
	mid = CSR_READ_2(sc, VTE_MID0L);
	sc->vte_eaddr[0] = (mid >> 0) & 0xFF;
	sc->vte_eaddr[1] = (mid >> 8) & 0xFF;
	mid = CSR_READ_2(sc, VTE_MID0M);
	sc->vte_eaddr[2] = (mid >> 0) & 0xFF;
	sc->vte_eaddr[3] = (mid >> 8) & 0xFF;
	mid = CSR_READ_2(sc, VTE_MID0H);
	sc->vte_eaddr[4] = (mid >> 0) & 0xFF;
	sc->vte_eaddr[5] = (mid >> 8) & 0xFF;
}