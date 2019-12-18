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
 int MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R88E_RF_WE_LUT ; 
 int /*<<< orphan*/  R92C_FPGA0_IQK ; 
 int /*<<< orphan*/  R92C_IQK_AGC_PTS ; 
 int /*<<< orphan*/  R92C_IQK_AGC_RSP ; 
 int /*<<< orphan*/  R92C_POWER_IQK_RESULT ; 
 int /*<<< orphan*/  R92C_RF_RCK_OS ; 
 int /*<<< orphan*/  R92C_RF_TXPA_G (int) ; 
 int /*<<< orphan*/  R92C_RX_IQK ; 
 int /*<<< orphan*/  R92C_RX_IQK_PI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_RX_IQK_TONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_RX_POWER_IQK_AFTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_RX_POWER_IQK_BEFORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_TX_IQK ; 
 int /*<<< orphan*/  R92C_TX_IQK_PI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_TX_IQK_TONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_TX_POWER_IQK_AFTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_TX_POWER_IQK_BEFORE (int /*<<< orphan*/ ) ; 
 int rtwn_bb_read (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_bb_write (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_rf_write (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
r88e_iq_calib_chain(struct rtwn_softc *sc, uint16_t tx[2], uint16_t rx[2])
{
	uint32_t status;

	/* Set Rx IQ calibration mode table. */
	rtwn_bb_write(sc, R92C_FPGA0_IQK, 0);
	rtwn_rf_write(sc, 0, R88E_RF_WE_LUT, 0x800a0);
	rtwn_rf_write(sc, 0, R92C_RF_RCK_OS, 0x30000);
	rtwn_rf_write(sc, 0, R92C_RF_TXPA_G(0), 0xf);
	rtwn_rf_write(sc, 0, R92C_RF_TXPA_G(1), 0xf117b);
	rtwn_bb_write(sc, R92C_FPGA0_IQK, 0x80800000);

	/* IQ calibration settings. */
	rtwn_bb_write(sc, R92C_TX_IQK, 0x01007c00);
	rtwn_bb_write(sc, R92C_RX_IQK, 0x81004800);

	/* IQ calibration settings for chain 0. */
	rtwn_bb_write(sc, R92C_TX_IQK_TONE(0), 0x10008c1c);
	rtwn_bb_write(sc, R92C_RX_IQK_TONE(0), 0x30008c1c);
	rtwn_bb_write(sc, R92C_TX_IQK_PI(0), 0x82160804);
	rtwn_bb_write(sc, R92C_RX_IQK_PI(0), 0x28160000);

	/* LO calibration settings. */
	rtwn_bb_write(sc, R92C_IQK_AGC_RSP, 0x0046a911);

	/* We're doing LO and IQ calibration in one shot. */
	rtwn_bb_write(sc, R92C_IQK_AGC_PTS, 0xf9000000);
	rtwn_bb_write(sc, R92C_IQK_AGC_PTS, 0xf8000000);

	/* Give LO and IQ calibrations the time to complete. */
	rtwn_delay(sc, 10000);

	/* Read IQ calibration status. */
	status = rtwn_bb_read(sc, R92C_RX_POWER_IQK_AFTER(0));
	if (status & (1 << 28))
		return (0);	/* Tx failed. */

	/* Read Tx IQ calibration results. */
	tx[0] = MS(rtwn_bb_read(sc, R92C_TX_POWER_IQK_BEFORE(0)),
	    R92C_POWER_IQK_RESULT);
	tx[1] = MS(rtwn_bb_read(sc, R92C_TX_POWER_IQK_AFTER(0)),
	    R92C_POWER_IQK_RESULT);
	if (tx[0] == 0x142 || tx[1] == 0x042)
		return (0);	/* Tx failed. */

	rtwn_bb_write(sc, R92C_TX_IQK, 0x80007c00 | (tx[0] << 16) | tx[1]);

	/* Set Rx IQ calibration mode table. */
	rtwn_bb_write(sc, R92C_FPGA0_IQK, 0);
	rtwn_rf_write(sc, 0, R88E_RF_WE_LUT, 0x800a0);
	rtwn_rf_write(sc, 0, R92C_RF_RCK_OS, 0x30000);
	rtwn_rf_write(sc, 0, R92C_RF_TXPA_G(0), 0xf);
	rtwn_rf_write(sc, 0, R92C_RF_TXPA_G(1), 0xf7ffa);
	rtwn_bb_write(sc, R92C_FPGA0_IQK, 0x80800000);

	/* IQ calibration settings. */
	rtwn_bb_write(sc, R92C_RX_IQK, 0x01004800);

	/* IQ calibration settings for chain 0. */
	rtwn_bb_write(sc, R92C_TX_IQK_TONE(0), 0x30008c1c);
	rtwn_bb_write(sc, R92C_RX_IQK_TONE(0), 0x10008c1c);
	rtwn_bb_write(sc, R92C_TX_IQK_PI(0), 0x82160c05);
	rtwn_bb_write(sc, R92C_RX_IQK_PI(0), 0x28160c05);

	/* LO calibration settings. */
	rtwn_bb_write(sc, R92C_IQK_AGC_RSP, 0x0046a911);

	/* We're doing LO and IQ calibration in one shot. */
	rtwn_bb_write(sc, R92C_IQK_AGC_PTS, 0xf9000000);
	rtwn_bb_write(sc, R92C_IQK_AGC_PTS, 0xf8000000);

	/* Give LO and IQ calibrations the time to complete. */
	rtwn_delay(sc, 10000);

	/* Read IQ calibration status. */
	status = rtwn_bb_read(sc, R92C_RX_POWER_IQK_AFTER(0));
	if (status & (1 << 27))
		return (1);	/* Rx failed. */

	/* Read Rx IQ calibration results. */
	rx[0] = MS(rtwn_bb_read(sc, R92C_RX_POWER_IQK_BEFORE(0)),
	    R92C_POWER_IQK_RESULT);
	rx[1] = MS(status, R92C_POWER_IQK_RESULT);
	if (rx[0] == 0x132 || rx[1] == 0x036)
		return (1);	/* Rx failed. */

	return (3);	/* Both Tx and Rx succeeded. */
}