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
typedef  int uint16_t ;
typedef  int u_int ;
struct run_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX0_2GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX0_CH100_TO_CH138_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX0_CH140_TO_CH165_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX0_CH36_TO_CH64_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX1_2GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX1_CH100_TO_CH138_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX1_CH140_TO_CH165_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_GAIN_CAL_TX1_CH36_TO_CH64_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX0_2GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX0_CH100_TO_CH138_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX0_CH140_TO_CH165_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX0_CH36_TO_CH64_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX1_2GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX1_CH100_TO_CH138_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX1_CH140_TO_CH165_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_IQ_PHASE_CAL_TX1_CH36_TO_CH64_5GHZ ; 
 int /*<<< orphan*/  RT5390_EEPROM_RF_IQ_COMPENSATION_CTL ; 
 int /*<<< orphan*/  RT5390_EEPROM_RF_IQ_IMBALANCE_COMPENSATION_CTL ; 
 int /*<<< orphan*/  run_bbp_write (struct run_softc*,int,int) ; 
 int /*<<< orphan*/  run_efuse_read (struct run_softc*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
run_iq_calib(struct run_softc *sc, u_int chan)
{
	uint16_t val;

	/* Tx0 IQ gain. */
	run_bbp_write(sc, 158, 0x2c);
	if (chan <= 14)
		run_efuse_read(sc, RT5390_EEPROM_IQ_GAIN_CAL_TX0_2GHZ, &val, 1);
	else if (chan <= 64) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_GAIN_CAL_TX0_CH36_TO_CH64_5GHZ,
		    &val, 1);
	} else if (chan <= 138) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_GAIN_CAL_TX0_CH100_TO_CH138_5GHZ,
		    &val, 1);
	} else if (chan <= 165) {
		run_efuse_read(sc,
	    RT5390_EEPROM_IQ_GAIN_CAL_TX0_CH140_TO_CH165_5GHZ,
		    &val, 1);
	} else
		val = 0;
	run_bbp_write(sc, 159, val);

	/* Tx0 IQ phase. */
	run_bbp_write(sc, 158, 0x2d);
	if (chan <= 14) {
		run_efuse_read(sc, RT5390_EEPROM_IQ_PHASE_CAL_TX0_2GHZ,
		    &val, 1);
	} else if (chan <= 64) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_PHASE_CAL_TX0_CH36_TO_CH64_5GHZ,
		    &val, 1);
	} else if (chan <= 138) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_PHASE_CAL_TX0_CH100_TO_CH138_5GHZ,
		    &val, 1);
	} else if (chan <= 165) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_PHASE_CAL_TX0_CH140_TO_CH165_5GHZ,
		    &val, 1);
	} else
		val = 0;
	run_bbp_write(sc, 159, val);

	/* Tx1 IQ gain. */
	run_bbp_write(sc, 158, 0x4a);
	if (chan <= 14) {
		run_efuse_read(sc, RT5390_EEPROM_IQ_GAIN_CAL_TX1_2GHZ,
		    &val, 1);
	} else if (chan <= 64) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_GAIN_CAL_TX1_CH36_TO_CH64_5GHZ,
		    &val, 1);
	} else if (chan <= 138) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_GAIN_CAL_TX1_CH100_TO_CH138_5GHZ,
		    &val, 1);
	} else if (chan <= 165) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_GAIN_CAL_TX1_CH140_TO_CH165_5GHZ,
		    &val, 1);
	} else
		val = 0;
	run_bbp_write(sc, 159, val);

	/* Tx1 IQ phase. */
	run_bbp_write(sc, 158, 0x4b);
	if (chan <= 14) {
		run_efuse_read(sc, RT5390_EEPROM_IQ_PHASE_CAL_TX1_2GHZ,
		    &val, 1);
	} else if (chan <= 64) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_PHASE_CAL_TX1_CH36_TO_CH64_5GHZ,
		    &val, 1);
	} else if (chan <= 138) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_PHASE_CAL_TX1_CH100_TO_CH138_5GHZ,
		    &val, 1);
	} else if (chan <= 165) {
		run_efuse_read(sc,
		    RT5390_EEPROM_IQ_PHASE_CAL_TX1_CH140_TO_CH165_5GHZ,
		    &val, 1);
	} else
		val = 0;
	run_bbp_write(sc, 159, val);

	/* RF IQ compensation control. */
	run_bbp_write(sc, 158, 0x04);
	run_efuse_read(sc, RT5390_EEPROM_RF_IQ_COMPENSATION_CTL,
	    &val, 1);
	run_bbp_write(sc, 159, val);

	/* RF IQ imbalance compensation control. */
	run_bbp_write(sc, 158, 0x03);
	run_efuse_read(sc,
	    RT5390_EEPROM_RF_IQ_IMBALANCE_COMPENSATION_CTL, &val, 1);
	run_bbp_write(sc, 159, val);
}