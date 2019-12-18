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
struct stge_softc {int dummy; } ;

/* Variables and functions */
 int CSR_READ_2 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EC_EepromBusy ; 
 int /*<<< orphan*/  STGE_EepromCtrl ; 
 int STGE_TIMEOUT ; 

__attribute__((used)) static int
stge_eeprom_wait(struct stge_softc *sc)
{
	int i;

	for (i = 0; i < STGE_TIMEOUT; i++) {
		DELAY(1000);
		if ((CSR_READ_2(sc, STGE_EepromCtrl) & EC_EepromBusy) == 0)
			return (0);
	}
	return (1);
}