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
typedef  scalar_t__ u_int ;
struct run_softc {int ntxchains; int nrxchains; int* txpow1; int* txpow2; int freq; } ;
struct rfprog {scalar_t__ chan; int r2; int r3; int r4; int r1; } ;
typedef  int int8_t ;

/* Variables and functions */
 struct rfprog* rt2860_rf2850 ; 
 int /*<<< orphan*/  run_delay (struct run_softc*,int) ; 
 int /*<<< orphan*/  run_rt2870_rf_write (struct run_softc*,int) ; 

__attribute__((used)) static void
run_rt2870_set_chan(struct run_softc *sc, u_int chan)
{
	const struct rfprog *rfprog = rt2860_rf2850;
	uint32_t r2, r3, r4;
	int8_t txpow1, txpow2;
	int i;

	/* find the settings for this channel (we know it exists) */
	for (i = 0; rfprog[i].chan != chan; i++);

	r2 = rfprog[i].r2;
	if (sc->ntxchains == 1)
		r2 |= 1 << 14;		/* 1T: disable Tx chain 2 */
	if (sc->nrxchains == 1)
		r2 |= 1 << 17 | 1 << 6;	/* 1R: disable Rx chains 2 & 3 */
	else if (sc->nrxchains == 2)
		r2 |= 1 << 6;		/* 2R: disable Rx chain 3 */

	/* use Tx power values from EEPROM */
	txpow1 = sc->txpow1[i];
	txpow2 = sc->txpow2[i];

	/* Initialize RF R3 and R4. */
	r3 = rfprog[i].r3 & 0xffffc1ff;
	r4 = (rfprog[i].r4 & ~(0x001f87c0)) | (sc->freq << 15);
	if (chan > 14) {
		if (txpow1 >= 0) {
			txpow1 = (txpow1 > 0xf) ? (0xf) : (txpow1);
			r3 |= (txpow1 << 10) | (1 << 9);
		} else {
			txpow1 += 7;

			/* txpow1 is not possible larger than 15. */
			r3 |= (txpow1 << 10);
		}
		if (txpow2 >= 0) {
			txpow2 = (txpow2 > 0xf) ? (0xf) : (txpow2);
			r4 |= (txpow2 << 7) | (1 << 6);
		} else {
			txpow2 += 7;
			r4 |= (txpow2 << 7);
		}
	} else {
		/* Set Tx0 power. */
		r3 |= (txpow1 << 9);

		/* Set frequency offset and Tx1 power. */
		r4 |= (txpow2 << 6);
	}

	run_rt2870_rf_write(sc, rfprog[i].r1);
	run_rt2870_rf_write(sc, r2);
	run_rt2870_rf_write(sc, r3 & ~(1 << 2));
	run_rt2870_rf_write(sc, r4);

	run_delay(sc, 10);

	run_rt2870_rf_write(sc, rfprog[i].r1);
	run_rt2870_rf_write(sc, r2);
	run_rt2870_rf_write(sc, r3 | (1 << 2));
	run_rt2870_rf_write(sc, r4);

	run_delay(sc, 10);

	run_rt2870_rf_write(sc, rfprog[i].r1);
	run_rt2870_rf_write(sc, r2);
	run_rt2870_rf_write(sc, r3 & ~(1 << 2));
	run_rt2870_rf_write(sc, r4);
}