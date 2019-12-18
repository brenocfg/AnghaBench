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
typedef  size_t u_int ;
struct rt2860_softc {int ntxchains; int nrxchains; int* txpow1; int* txpow2; int freq; } ;
struct rfprog {size_t chan; int r2; int r3; int r4; int r1; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RT2860_RF1 ; 
 int /*<<< orphan*/  RT2860_RF2 ; 
 int /*<<< orphan*/  RT2860_RF3 ; 
 int /*<<< orphan*/  RT2860_RF4 ; 
 struct rfprog* rt2860_rf2850 ; 
 int /*<<< orphan*/  rt2860_rf_write (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rt2860_set_chan(struct rt2860_softc *sc, u_int chan)
{
	const struct rfprog *rfprog = rt2860_rf2850;
	uint32_t r2, r3, r4;
	int8_t txpow1, txpow2;
	u_int i;

	/* find the settings for this channel (we know it exists) */
	for (i = 0; rfprog[i].chan != chan; i++);

	r2 = rfprog[i].r2;
	if (sc->ntxchains == 1)
		r2 |= 1 << 12;		/* 1T: disable Tx chain 2 */
	if (sc->nrxchains == 1)
		r2 |= 1 << 15 | 1 << 4;	/* 1R: disable Rx chains 2 & 3 */
	else if (sc->nrxchains == 2)
		r2 |= 1 << 4;		/* 2R: disable Rx chain 3 */

	/* use Tx power values from EEPROM */
	txpow1 = sc->txpow1[i];
	txpow2 = sc->txpow2[i];
	if (chan > 14) {
		if (txpow1 >= 0)
			txpow1 = txpow1 << 1 | 1;
		else
			txpow1 = (7 + txpow1) << 1;
		if (txpow2 >= 0)
			txpow2 = txpow2 << 1 | 1;
		else
			txpow2 = (7 + txpow2) << 1;
	}
	r3 = rfprog[i].r3 | txpow1 << 7;
	r4 = rfprog[i].r4 | sc->freq << 13 | txpow2 << 4;

	rt2860_rf_write(sc, RT2860_RF1, rfprog[i].r1);
	rt2860_rf_write(sc, RT2860_RF2, r2);
	rt2860_rf_write(sc, RT2860_RF3, r3);
	rt2860_rf_write(sc, RT2860_RF4, r4);

	DELAY(200);

	rt2860_rf_write(sc, RT2860_RF1, rfprog[i].r1);
	rt2860_rf_write(sc, RT2860_RF2, r2);
	rt2860_rf_write(sc, RT2860_RF3, r3 | 1);
	rt2860_rf_write(sc, RT2860_RF4, r4);

	DELAY(200);

	rt2860_rf_write(sc, RT2860_RF1, rfprog[i].r1);
	rt2860_rf_write(sc, RT2860_RF2, r2);
	rt2860_rf_write(sc, RT2860_RF3, r3);
	rt2860_rf_write(sc, RT2860_RF4, r4);
}