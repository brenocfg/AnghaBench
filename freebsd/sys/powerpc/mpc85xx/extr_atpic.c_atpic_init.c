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
struct atpic_softc {int* sc_mask; } ;

/* Variables and functions */
 int ATPIC_MASTER ; 
 int ATPIC_SLAVE ; 
 int ICW1_IC4 ; 
 int ICW1_RESET ; 
 int ICW4_8086 ; 
 int OCW3_RR ; 
 int OCW3_SEL ; 
 int /*<<< orphan*/  atpic_write (struct atpic_softc*,int,int,int) ; 

__attribute__((used)) static void
atpic_init(struct atpic_softc *sc, int icu)
{

	sc->sc_mask[icu] = 0xff - ((icu == ATPIC_MASTER) ? 4 : 0);

	atpic_write(sc, icu, 0, ICW1_RESET | ICW1_IC4);
	atpic_write(sc, icu, 1, (icu == ATPIC_SLAVE) ? 8 : 0);
	atpic_write(sc, icu, 1, (icu == ATPIC_SLAVE) ? 2 : 4);
	atpic_write(sc, icu, 1, ICW4_8086);
	atpic_write(sc, icu, 1, sc->sc_mask[icu]);
	atpic_write(sc, icu, 0, OCW3_SEL | OCW3_RR);
}