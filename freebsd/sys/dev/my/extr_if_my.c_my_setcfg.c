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
struct my_softc {int /*<<< orphan*/  my_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct my_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MY_CLRBIT (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int MY_FD ; 
 int /*<<< orphan*/  MY_LOCK_ASSERT (struct my_softc*) ; 
 int MY_PS10 ; 
 int MY_PS1000 ; 
 int MY_RE ; 
 int MY_RXRUN ; 
 int /*<<< orphan*/  MY_SETBIT (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MY_TCRRCR ; 
 int MY_TE ; 
 int MY_TIMEOUT ; 
 int MY_TXRUN ; 
 int PHY_BMCR_1000 ; 
 int PHY_BMCR_DUPLEX ; 
 int PHY_BMCR_SPEEDSEL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
my_setcfg(struct my_softc * sc, int bmcr)
{
	int             i, restart = 0;

	MY_LOCK_ASSERT(sc);
	if (CSR_READ_4(sc, MY_TCRRCR) & (MY_TE | MY_RE)) {
		restart = 1;
		MY_CLRBIT(sc, MY_TCRRCR, (MY_TE | MY_RE));
		for (i = 0; i < MY_TIMEOUT; i++) {
			DELAY(10);
			if (!(CSR_READ_4(sc, MY_TCRRCR) &
			    (MY_TXRUN | MY_RXRUN)))
				break;
		}
		if (i == MY_TIMEOUT)
			device_printf(sc->my_dev,
			    "failed to force tx and rx to idle \n");
	}
	MY_CLRBIT(sc, MY_TCRRCR, MY_PS1000);
	MY_CLRBIT(sc, MY_TCRRCR, MY_PS10);
	if (bmcr & PHY_BMCR_1000)
		MY_SETBIT(sc, MY_TCRRCR, MY_PS1000);
	else if (!(bmcr & PHY_BMCR_SPEEDSEL))
		MY_SETBIT(sc, MY_TCRRCR, MY_PS10);
	if (bmcr & PHY_BMCR_DUPLEX)
		MY_SETBIT(sc, MY_TCRRCR, MY_FD);
	else
		MY_CLRBIT(sc, MY_TCRRCR, MY_FD);
	if (restart)
		MY_SETBIT(sc, MY_TCRRCR, MY_TE | MY_RE);
	return;
}