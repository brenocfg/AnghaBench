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
typedef  int uint16_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_OFDM0_AGCRSSITABLE ; 
 int /*<<< orphan*/  R92C_OFDM0_ECCATHRESHOLD ; 
 int /*<<< orphan*/  R92C_OFDM0_RXIQEXTANTA ; 
 int /*<<< orphan*/  R92C_OFDM0_RXIQIMBALANCE (int) ; 
 int /*<<< orphan*/  R92C_OFDM0_TXAFE (int) ; 
 int /*<<< orphan*/  R92C_OFDM0_TXIQIMBALANCE (int) ; 
 int rtwn_bb_read (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_setbits (struct rtwn_softc*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
r92c_iq_calib_write_results(struct rtwn_softc *sc, uint16_t tx[2],
    uint16_t rx[2], int chain)
{
	uint32_t reg, val, x;
	long y, tx_c;

	if (tx[0] == 0xff || tx[1] == 0xff)
		return;

	reg = rtwn_bb_read(sc, R92C_OFDM0_TXIQIMBALANCE(chain));
	val = ((reg >> 22) & 0x3ff);
	x = tx[0];
	if (x & 0x00000200)
		x |= 0xfffffc00;
	reg = (((x * val) >> 8) & 0x3ff);
	rtwn_bb_setbits(sc, R92C_OFDM0_TXIQIMBALANCE(chain), 0x3ff, reg);
	rtwn_bb_setbits(sc, R92C_OFDM0_ECCATHRESHOLD, 0x80000000,
	    ((x * val) & 0x80) << 24);

	y = tx[1];
	if (y & 0x00000200)
		y |= 0xfffffc00;
	tx_c = (y * val) >> 8;
	rtwn_bb_setbits(sc, R92C_OFDM0_TXAFE(chain), 0xf0000000,
	    (tx_c & 0x3c0) << 22);
	rtwn_bb_setbits(sc, R92C_OFDM0_TXIQIMBALANCE(chain), 0x003f0000,
	    (tx_c & 0x3f) << 16);
	rtwn_bb_setbits(sc, R92C_OFDM0_ECCATHRESHOLD, 0x20000000,
	    ((y * val) & 0x80) << 22);

	if (rx[0] == 0xff || rx[1] == 0xff)
		return;

	rtwn_bb_setbits(sc, R92C_OFDM0_RXIQIMBALANCE(chain), 0x3ff,
	    rx[0] & 0x3ff);
	rtwn_bb_setbits(sc, R92C_OFDM0_RXIQIMBALANCE(chain), 0xfc00,
	    (rx[1] & 0x3f) << 10);

	if (chain == 0) {
		rtwn_bb_setbits(sc, R92C_OFDM0_RXIQEXTANTA, 0xf0000000,
		    (rx[1] & 0x3c0) << 22);
	} else {
		rtwn_bb_setbits(sc, R92C_OFDM0_AGCRSSITABLE, 0xf000,
		    (rx[1] & 0x3c0) << 6);
	}
}