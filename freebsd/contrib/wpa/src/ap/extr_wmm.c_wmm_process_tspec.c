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
typedef  unsigned int u64 ;
typedef  int u16 ;
struct wmm_tspec_element {int* ts_info; int /*<<< orphan*/  medium_time; int /*<<< orphan*/  surplus_bandwidth_allowance; int /*<<< orphan*/  minimum_phy_rate; int /*<<< orphan*/  nominal_msdu_size; int /*<<< orphan*/  mean_data_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WMM_ADDTS_STATUS_ADMISSION_ACCEPTED ; 
 int WMM_ADDTS_STATUS_INVALID_PARAMETERS ; 
 int WMM_ADDTS_STATUS_REFUSED ; 
 int /*<<< orphan*/  host_to_le16 (unsigned int) ; 
 int le_to_host16 (int /*<<< orphan*/ ) ; 
 int le_to_host32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int wmm_process_tspec(struct wmm_tspec_element *tspec)
{
	u64 medium_time;
	unsigned int pps, duration;
	unsigned int up, psb, dir, tid;
	u16 val, surplus;

	up = (tspec->ts_info[1] >> 3) & 0x07;
	psb = (tspec->ts_info[1] >> 2) & 0x01;
	dir = (tspec->ts_info[0] >> 5) & 0x03;
	tid = (tspec->ts_info[0] >> 1) & 0x0f;
	wpa_printf(MSG_DEBUG, "WMM: TS Info: UP=%d PSB=%d Direction=%d TID=%d",
		   up, psb, dir, tid);
	val = le_to_host16(tspec->nominal_msdu_size);
	wpa_printf(MSG_DEBUG, "WMM: Nominal MSDU Size: %d%s",
		   val & 0x7fff, val & 0x8000 ? " (fixed)" : "");
	wpa_printf(MSG_DEBUG, "WMM: Mean Data Rate: %u bps",
		   le_to_host32(tspec->mean_data_rate));
	wpa_printf(MSG_DEBUG, "WMM: Minimum PHY Rate: %u bps",
		   le_to_host32(tspec->minimum_phy_rate));
	val = le_to_host16(tspec->surplus_bandwidth_allowance);
	wpa_printf(MSG_DEBUG, "WMM: Surplus Bandwidth Allowance: %u.%04u",
		   val >> 13, 10000 * (val & 0x1fff) / 0x2000);

	val = le_to_host16(tspec->nominal_msdu_size);
	if (val == 0) {
		wpa_printf(MSG_DEBUG, "WMM: Invalid Nominal MSDU Size (0)");
		return WMM_ADDTS_STATUS_INVALID_PARAMETERS;
	}
	/* pps = Ceiling((Mean Data Rate / 8) / Nominal MSDU Size) */
	pps = ((le_to_host32(tspec->mean_data_rate) / 8) + val - 1) / val;
	wpa_printf(MSG_DEBUG, "WMM: Packets-per-second estimate for TSPEC: %d",
		   pps);

	if (le_to_host32(tspec->minimum_phy_rate) < 1000000) {
		wpa_printf(MSG_DEBUG, "WMM: Too small Minimum PHY Rate");
		return WMM_ADDTS_STATUS_INVALID_PARAMETERS;
	}

	duration = (le_to_host16(tspec->nominal_msdu_size) & 0x7fff) * 8 /
		(le_to_host32(tspec->minimum_phy_rate) / 1000000) +
		50 /* FIX: proper SIFS + ACK duration */;

	/* unsigned binary number with an implicit binary point after the
	 * leftmost 3 bits, i.e., 0x2000 = 1.0 */
	surplus = le_to_host16(tspec->surplus_bandwidth_allowance);
	if (surplus <= 0x2000) {
		wpa_printf(MSG_DEBUG, "WMM: Surplus Bandwidth Allowance not "
			   "greater than unity");
		return WMM_ADDTS_STATUS_INVALID_PARAMETERS;
	}

	medium_time = (u64) surplus * pps * duration / 0x2000;
	wpa_printf(MSG_DEBUG, "WMM: Estimated medium time: %lu",
		   (unsigned long) medium_time);

	/*
	 * TODO: store list of granted (and still active) TSPECs and check
	 * whether there is available medium time for this request. For now,
	 * just refuse requests that would by themselves take very large
	 * portion of the available bandwidth.
	 */
	if (medium_time > 750000) {
		wpa_printf(MSG_DEBUG, "WMM: Refuse TSPEC request for over "
			   "75%% of available bandwidth");
		return WMM_ADDTS_STATUS_REFUSED;
	}

	/* Convert to 32 microseconds per second unit */
	tspec->medium_time = host_to_le16(medium_time / 32);

	return WMM_ADDTS_STATUS_ADMISSION_ACCEPTED;
}