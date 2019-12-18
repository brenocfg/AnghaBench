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
struct emac_softc {int dummy; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  EMAC_MAC_MIND ; 
 int EMAC_READ_REG (struct emac_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
emac_miibus_iowait(struct emac_softc *sc)
{
	uint32_t timeout;

	for (timeout = 100; timeout != 0; --timeout) {
		DELAY(100);
		if ((EMAC_READ_REG(sc, EMAC_MAC_MIND) & 0x1) == 0)
			return (true);
	}

	return (false);
}