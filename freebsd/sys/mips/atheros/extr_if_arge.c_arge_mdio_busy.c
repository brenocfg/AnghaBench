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
struct arge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_MAC_MII_INDICATOR ; 
 int /*<<< orphan*/  ARGE_MDIO_BARRIER_READ (struct arge_softc*) ; 
 int ARGE_MDIO_READ (struct arge_softc*,int /*<<< orphan*/ ) ; 
 int ARGE_MII_TIMEOUT ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static int
arge_mdio_busy(struct arge_softc *sc)
{
	int i,result;

	for (i = 0; i < ARGE_MII_TIMEOUT; i++) {
		DELAY(5);
		ARGE_MDIO_BARRIER_READ(sc);
		result = ARGE_MDIO_READ(sc, AR71XX_MAC_MII_INDICATOR);
		if (! result)
			return (0);
		DELAY(5);
	}
	return (-1);
}