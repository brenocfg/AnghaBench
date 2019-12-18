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
typedef  unsigned int u8 ;
struct wpa_bss {int /*<<< orphan*/  caps; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  tsf; } ;
struct rrm_measurement_report_element {int dummy; } ;
struct rrm_measurement_beacon_report {int dummy; } ;
struct bitfield {int dummy; } ;
typedef  enum beacon_report_detail { ____Placeholder_beacon_report_detail } beacon_report_detail ;

/* Variables and functions */
 int BEACON_REPORT_DETAIL_ALL_FIELDS_AND_ELEMENTS ; 
 int BEACON_REPORT_DETAIL_NONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int REPORTED_FRAME_BODY_SUBELEM_LEN ; 
 int /*<<< orphan*/  WLAN_BEACON_REPORT_SUBELEM_FRAME_BODY ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PUT_LE64 (unsigned int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bitfield_is_set (struct bitfield*,unsigned int) ; 
 int /*<<< orphan*/  os_memcpy (unsigned int*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wpas_beacon_rep_add_frame_body(struct bitfield *eids,
					  enum beacon_report_detail detail,
					  struct wpa_bss *bss, u8 *buf,
					  size_t buf_len, u8 **ies_buf,
					  size_t *ie_len, int add_fixed)
{
	u8 *ies = *ies_buf;
	size_t ies_len = *ie_len;
	u8 *pos = buf;
	int rem_len;

	rem_len = 255 - sizeof(struct rrm_measurement_beacon_report) -
		sizeof(struct rrm_measurement_report_element) - 2 -
		REPORTED_FRAME_BODY_SUBELEM_LEN;

	if (detail > BEACON_REPORT_DETAIL_ALL_FIELDS_AND_ELEMENTS) {
		wpa_printf(MSG_DEBUG,
			   "Beacon Request: Invalid reporting detail: %d",
			   detail);
		return -1;
	}

	if (detail == BEACON_REPORT_DETAIL_NONE)
		return 0;

	/*
	 * Minimal frame body subelement size: EID(1) + length(1) + TSF(8) +
	 * beacon interval(2) + capabilities(2) = 14 bytes
	 */
	if (add_fixed && buf_len < 14)
		return -1;

	*pos++ = WLAN_BEACON_REPORT_SUBELEM_FRAME_BODY;
	/* The length will be filled later */
	pos++;

	if (add_fixed) {
		WPA_PUT_LE64(pos, bss->tsf);
		pos += sizeof(bss->tsf);
		WPA_PUT_LE16(pos, bss->beacon_int);
		pos += 2;
		WPA_PUT_LE16(pos, bss->caps);
		pos += 2;
	}

	rem_len -= pos - buf;

	/*
	 * According to IEEE Std 802.11-2016, 9.4.2.22.7, if the reported frame
	 * body subelement causes the element to exceed the maximum element
	 * size, the subelement is truncated so that the last IE is a complete
	 * IE. So even when required to report all IEs, add elements one after
	 * the other and stop once there is no more room in the measurement
	 * element.
	 */
	while (ies_len > 2 && 2U + ies[1] <= ies_len && rem_len > 0) {
		if (detail == BEACON_REPORT_DETAIL_ALL_FIELDS_AND_ELEMENTS ||
		    (eids && bitfield_is_set(eids, ies[0]))) {
			u8 elen = ies[1];

			if (2 + elen > buf + buf_len - pos ||
			    2 + elen > rem_len)
				break;

			*pos++ = ies[0];
			*pos++ = elen;
			os_memcpy(pos, ies + 2, elen);
			pos += elen;
			rem_len -= 2 + elen;
		}

		ies_len -= 2 + ies[1];
		ies += 2 + ies[1];
	}

	*ie_len = ies_len;
	*ies_buf = ies;

	/* Now the length is known */
	buf[1] = pos - buf - 2;
	return pos - buf;
}