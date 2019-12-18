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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct otus_softc {int dummy; } ;
struct ieee80211_channel {int ic_freq; } ;

/* Variables and functions */
 int AR_BANK4_ADDR (int) ; 
 int AR_BANK4_AMODE_REFSEL (int) ; 
 int AR_BANK4_BMODE_LF_SYNTH_FREQ ; 
 int AR_BANK4_CHUP ; 
 int /*<<< orphan*/  AR_PHY (int) ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_delay_ms (struct otus_softc*,int) ; 
 int otus_reverse_bits (int) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int) ; 
 int otus_write_barrier (struct otus_softc*) ; 

int
otus_set_rf_bank4(struct otus_softc *sc, struct ieee80211_channel *c)
{
	uint8_t chansel, d0, d1;
	uint16_t data;
	int error;

	OTUS_LOCK_ASSERT(sc);

	d0 = 0;
	if (IEEE80211_IS_CHAN_5GHZ(c)) {
		chansel = (c->ic_freq - 4800) / 5;
		if (chansel & 1)
			d0 |= AR_BANK4_AMODE_REFSEL(2);
		else
			d0 |= AR_BANK4_AMODE_REFSEL(1);
	} else {
		d0 |= AR_BANK4_AMODE_REFSEL(2);
		if (c->ic_freq == 2484) {	/* CH 14 */
			d0 |= AR_BANK4_BMODE_LF_SYNTH_FREQ;
			chansel = 10 + (c->ic_freq - 2274) / 5;
		} else
			chansel = 16 + (c->ic_freq - 2272) / 5;
		chansel <<= 2;
	}
	d0 |= AR_BANK4_ADDR(1) | AR_BANK4_CHUP;
	d1 = otus_reverse_bits(chansel);

	/* Write bits 0-4 of d0 and d1. */
	data = (d1 & 0x1f) << 5 | (d0 & 0x1f);
	otus_write(sc, AR_PHY(44), data);
	/* Write bits 5-7 of d0 and d1. */
	data = (d1 >> 5) << 5 | (d0 >> 5);
	otus_write(sc, AR_PHY(58), data);

	if ((error = otus_write_barrier(sc)) == 0)
		otus_delay_ms(sc, 10);
	return error;
}