#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  channel_type; int /*<<< orphan*/  center_freq; } ;
struct bwn_phy_n {int hang_avoid; int mphase_cal_phase_id; size_t* mphase_txcal_bestcoeffs; int txiqlocal_coeffsvalid; size_t* txiqlocal_bestc; size_t mphase_txcal_cmdidx; TYPE_1__ txiqlocal_chanspec; scalar_t__ mphase_txcal_numcmds; scalar_t__ ipa2g_on; } ;
struct bwn_phy {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_nphy_txgains {int dummy; } ;
struct bwn_nphy_iqcal_params {size_t cal_gain; int* ncorr; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_BAND_2G ; 
 int /*<<< orphan*/  BWN_NPHY_IQLOCAL_CMD ; 
 int /*<<< orphan*/  BWN_NPHY_IQLOCAL_CMDGCTL ; 
 int /*<<< orphan*/  BWN_NPHY_IQLOCAL_CMDNNUM ; 
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 size_t BWN_NTAB_TX_IQLO_CAL_CMDS_FULLCAL ; 
 size_t BWN_NTAB_TX_IQLO_CAL_CMDS_FULLCAL_REV3 ; 
 size_t BWN_NTAB_TX_IQLO_CAL_CMDS_RECAL ; 
 size_t BWN_NTAB_TX_IQLO_CAL_CMDS_RECAL_REV3 ; 
 int BWN_NTAB_TX_IQLO_CAL_STARTCOEFS ; 
 int BWN_NTAB_TX_IQLO_CAL_STARTCOEFS_REV3 ; 
 size_t BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_get_centre_freq (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_get_chan_type (struct bwn_mac*,int /*<<< orphan*/ *) ; 
 scalar_t__ bwn_is_40mhz (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_iq_cal_gain_params (struct bwn_mac*,int,struct bwn_nphy_txgains,struct bwn_nphy_iqcal_params*) ; 
 int /*<<< orphan*/  bwn_nphy_run_samples (struct bwn_mac*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_nphy_stop_playback (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tx_cal_phy_cleanup (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tx_cal_phy_setup (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tx_cal_radio_setup (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_tx_iq_workaround (struct bwn_mac*) ; 
 int bwn_nphy_tx_tone (struct bwn_mac*,int,int,int,int,int) ; 
 int /*<<< orphan*/  bwn_nphy_update_tx_cal_ladder (struct bwn_mac*,size_t) ; 
 size_t bwn_ntab_read (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_ntab_read_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,size_t*) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_ntab_write_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,size_t const*) ; 
 size_t min (size_t,size_t) ; 
 size_t* tbl_tx_iqlo_cal_cmds_fullcal ; 
 size_t* tbl_tx_iqlo_cal_cmds_fullcal_nphyrev3 ; 
 size_t* tbl_tx_iqlo_cal_cmds_recal ; 
 size_t* tbl_tx_iqlo_cal_cmds_recal_nphyrev3 ; 
 size_t* tbl_tx_iqlo_cal_iqimb_ladder_20 ; 
 size_t* tbl_tx_iqlo_cal_iqimb_ladder_40 ; 
 size_t* tbl_tx_iqlo_cal_loft_ladder_20 ; 
 size_t* tbl_tx_iqlo_cal_loft_ladder_40 ; 
 size_t* tbl_tx_iqlo_cal_startcoefs ; 
 size_t* tbl_tx_iqlo_cal_startcoefs_nphyrev3 ; 

__attribute__((used)) static int bwn_nphy_cal_tx_iq_lo(struct bwn_mac *mac,
				struct bwn_nphy_txgains target,
				bool full, bool mphase)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	int i;
	int error = 0;
	int freq;
	bool avoid = false;
	uint8_t length;
	uint16_t tmp, core, type, count, max, numb, last = 0, cmd;
	const uint16_t *table;
	bool phy6or5x;

	uint16_t buffer[11];
	uint16_t diq_start = 0;
	uint16_t save[2];
	uint16_t gain[2];
	struct bwn_nphy_iqcal_params params[2];
	bool updated[2] = { };

	bwn_nphy_stay_in_carrier_search(mac, true);

	if (mac->mac_phy.rev >= 4) {
		avoid = nphy->hang_avoid;
		nphy->hang_avoid = false;
	}

	bwn_ntab_read_bulk(mac, BWN_NTAB16(7, 0x110), 2, save);

	for (i = 0; i < 2; i++) {
		bwn_nphy_iq_cal_gain_params(mac, i, target, &params[i]);
		gain[i] = params[i].cal_gain;
	}

	bwn_ntab_write_bulk(mac, BWN_NTAB16(7, 0x110), 2, gain);

	bwn_nphy_tx_cal_radio_setup(mac);
	bwn_nphy_tx_cal_phy_setup(mac);

	phy6or5x = mac->mac_phy.rev >= 6 ||
		(mac->mac_phy.rev == 5 && nphy->ipa2g_on &&
		bwn_current_band(mac) == BWN_BAND_2G);
	if (phy6or5x) {
		if (bwn_is_40mhz(mac)) {
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 0), 18,
					tbl_tx_iqlo_cal_loft_ladder_40);
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 32), 18,
					tbl_tx_iqlo_cal_iqimb_ladder_40);
		} else {
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 0), 18,
					tbl_tx_iqlo_cal_loft_ladder_20);
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 32), 18,
					tbl_tx_iqlo_cal_iqimb_ladder_20);
		}
	}

	if (phy->rev >= 19) {
		/* TODO */
	} else if (phy->rev >= 7) {
		BWN_PHY_WRITE(mac, BWN_NPHY_IQLOCAL_CMDGCTL, 0x8AD9);
	} else {
		BWN_PHY_WRITE(mac, BWN_NPHY_IQLOCAL_CMDGCTL, 0x8AA9);
	}

	if (!bwn_is_40mhz(mac))
		freq = 2500;
	else
		freq = 5000;

	if (nphy->mphase_cal_phase_id > 2)
		bwn_nphy_run_samples(mac, (bwn_is_40mhz(mac) ? 40 : 20) * 8,
				     0xFFFF, 0, true, false, false);
	else
		error = bwn_nphy_tx_tone(mac, freq, 250, true, false, false);

	if (error == 0) {
		if (nphy->mphase_cal_phase_id > 2) {
			table = nphy->mphase_txcal_bestcoeffs;
			length = 11;
			if (mac->mac_phy.rev < 3)
				length -= 2;
		} else {
			if (!full && nphy->txiqlocal_coeffsvalid) {
				table = nphy->txiqlocal_bestc;
				length = 11;
				if (mac->mac_phy.rev < 3)
					length -= 2;
			} else {
				full = true;
				if (mac->mac_phy.rev >= 3) {
					table = tbl_tx_iqlo_cal_startcoefs_nphyrev3;
					length = BWN_NTAB_TX_IQLO_CAL_STARTCOEFS_REV3;
				} else {
					table = tbl_tx_iqlo_cal_startcoefs;
					length = BWN_NTAB_TX_IQLO_CAL_STARTCOEFS;
				}
			}
		}

		bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 64), length, table);

		if (full) {
			if (mac->mac_phy.rev >= 3)
				max = BWN_NTAB_TX_IQLO_CAL_CMDS_FULLCAL_REV3;
			else
				max = BWN_NTAB_TX_IQLO_CAL_CMDS_FULLCAL;
		} else {
			if (mac->mac_phy.rev >= 3)
				max = BWN_NTAB_TX_IQLO_CAL_CMDS_RECAL_REV3;
			else
				max = BWN_NTAB_TX_IQLO_CAL_CMDS_RECAL;
		}

		if (mphase) {
			count = nphy->mphase_txcal_cmdidx;
			numb = min(max,
				(uint16_t)(count + nphy->mphase_txcal_numcmds));
		} else {
			count = 0;
			numb = max;
		}

		for (; count < numb; count++) {
			if (full) {
				if (mac->mac_phy.rev >= 3)
					cmd = tbl_tx_iqlo_cal_cmds_fullcal_nphyrev3[count];
				else
					cmd = tbl_tx_iqlo_cal_cmds_fullcal[count];
			} else {
				if (mac->mac_phy.rev >= 3)
					cmd = tbl_tx_iqlo_cal_cmds_recal_nphyrev3[count];
				else
					cmd = tbl_tx_iqlo_cal_cmds_recal[count];
			}

			core = (cmd & 0x3000) >> 12;
			type = (cmd & 0x0F00) >> 8;

			if (phy6or5x && updated[core] == 0) {
				bwn_nphy_update_tx_cal_ladder(mac, core);
				updated[core] = true;
			}

			tmp = (params[core].ncorr[type] << 8) | 0x66;
			BWN_PHY_WRITE(mac, BWN_NPHY_IQLOCAL_CMDNNUM, tmp);

			if (type == 1 || type == 3 || type == 4) {
				buffer[0] = bwn_ntab_read(mac,
						BWN_NTAB16(15, 69 + core));
				diq_start = buffer[0];
				buffer[0] = 0;
				bwn_ntab_write(mac, BWN_NTAB16(15, 69 + core),
						0);
			}

			BWN_PHY_WRITE(mac, BWN_NPHY_IQLOCAL_CMD, cmd);
			for (i = 0; i < 2000; i++) {
				tmp = BWN_PHY_READ(mac, BWN_NPHY_IQLOCAL_CMD);
				if (tmp & 0xC000)
					break;
				DELAY(10);
			}

			bwn_ntab_read_bulk(mac, BWN_NTAB16(15, 96), length,
						buffer);
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 64), length,
						buffer);

			if (type == 1 || type == 3 || type == 4)
				buffer[0] = diq_start;
		}

		if (mphase)
			nphy->mphase_txcal_cmdidx = (numb >= max) ? 0 : numb;

		last = (mac->mac_phy.rev < 3) ? 6 : 7;

		if (!mphase || nphy->mphase_cal_phase_id == last) {
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 96), 4, buffer);
			bwn_ntab_read_bulk(mac, BWN_NTAB16(15, 80), 4, buffer);
			if (mac->mac_phy.rev < 3) {
				buffer[0] = 0;
				buffer[1] = 0;
				buffer[2] = 0;
				buffer[3] = 0;
			}
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 88), 4,
						buffer);
			bwn_ntab_read_bulk(mac, BWN_NTAB16(15, 101), 2,
						buffer);
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 85), 2,
						buffer);
			bwn_ntab_write_bulk(mac, BWN_NTAB16(15, 93), 2,
						buffer);
			length = 11;
			if (mac->mac_phy.rev < 3)
				length -= 2;
			bwn_ntab_read_bulk(mac, BWN_NTAB16(15, 96), length,
						nphy->txiqlocal_bestc);
			nphy->txiqlocal_coeffsvalid = true;
			nphy->txiqlocal_chanspec.center_freq =
						bwn_get_centre_freq(mac);
			nphy->txiqlocal_chanspec.channel_type = bwn_get_chan_type(mac, NULL);
		} else {
			length = 11;
			if (mac->mac_phy.rev < 3)
				length -= 2;
			bwn_ntab_read_bulk(mac, BWN_NTAB16(15, 96), length,
						nphy->mphase_txcal_bestcoeffs);
		}

		bwn_nphy_stop_playback(mac);
		BWN_PHY_WRITE(mac, BWN_NPHY_IQLOCAL_CMDGCTL, 0);
	}

	bwn_nphy_tx_cal_phy_cleanup(mac);
	bwn_ntab_write_bulk(mac, BWN_NTAB16(7, 0x110), 2, save);

	if (mac->mac_phy.rev < 2 && (!mphase || nphy->mphase_cal_phase_id == last))
		bwn_nphy_tx_iq_workaround(mac);

	if (mac->mac_phy.rev >= 4)
		nphy->hang_avoid = avoid;

	bwn_nphy_stay_in_carrier_search(mac, false);

	return error;
}