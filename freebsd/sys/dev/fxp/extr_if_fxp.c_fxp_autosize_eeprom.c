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
struct fxp_softc {int eeprom_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  fxp_eeprom_getword (struct fxp_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fxp_autosize_eeprom(struct fxp_softc *sc)
{

	/* guess maximum size of 256 words */
	sc->eeprom_size = 8;

	/* autosize */
	(void) fxp_eeprom_getword(sc, 0, 1);
}