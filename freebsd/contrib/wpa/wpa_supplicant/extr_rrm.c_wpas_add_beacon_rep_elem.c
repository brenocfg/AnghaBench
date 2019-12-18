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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct wpabuf {int dummy; } ;
struct wpa_bss {int dummy; } ;
struct rrm_measurement_beacon_report {int dummy; } ;
struct beacon_rep_data {scalar_t__ report_detail; int /*<<< orphan*/  token; scalar_t__ last_indication; int /*<<< orphan*/  eids; } ;

/* Variables and functions */
 scalar_t__ BEACON_REPORT_DETAIL_NONE ; 
 int /*<<< orphan*/  BEACON_REPORT_LAST_INDICATION_SUBELEM_LEN ; 
 int /*<<< orphan*/  MEASUREMENT_REPORT_MODE_ACCEPT ; 
 int /*<<< orphan*/  MEASURE_TYPE_BEACON ; 
 int REPORTED_FRAME_BODY_MORE_FRAGMENTS ; 
 scalar_t__ REPORTED_FRAME_BODY_SUBELEM_LEN ; 
 int WLAN_BEACON_REPORT_SUBELEM_FRAME_BODY_FRAGMENT_ID ; 
 int WLAN_BEACON_REPORT_SUBELEM_LAST_INDICATION ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int* os_malloc (scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (int*,struct rrm_measurement_beacon_report*,int) ; 
 int wpas_beacon_rep_add_frame_body (int /*<<< orphan*/ ,scalar_t__,struct wpa_bss*,int*,int,int**,size_t*,int) ; 
 int wpas_rrm_report_elem (struct wpabuf**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__) ; 

__attribute__((used)) static int wpas_add_beacon_rep_elem(struct beacon_rep_data *data,
				    struct wpa_bss *bss,
				    struct wpabuf **wpa_buf,
				    struct rrm_measurement_beacon_report *rep,
				    u8 **ie, size_t *ie_len, u8 idx)
{
	int ret;
	u8 *buf, *pos;
	u32 subelems_len = REPORTED_FRAME_BODY_SUBELEM_LEN +
		(data->last_indication ?
		 BEACON_REPORT_LAST_INDICATION_SUBELEM_LEN : 0);

	/* Maximum element length: Beacon Report element + Reported Frame Body
	 * subelement + all IEs of the reported Beacon frame + Reported Frame
	 * Body Fragment ID subelement */
	buf = os_malloc(sizeof(*rep) + 14 + *ie_len + subelems_len);
	if (!buf)
		return -1;

	os_memcpy(buf, rep, sizeof(*rep));

	ret = wpas_beacon_rep_add_frame_body(data->eids, data->report_detail,
					     bss, buf + sizeof(*rep),
					     14 + *ie_len, ie, ie_len,
					     idx == 0);
	if (ret < 0)
		goto out;

	pos = buf + ret + sizeof(*rep);
	pos[0] = WLAN_BEACON_REPORT_SUBELEM_FRAME_BODY_FRAGMENT_ID;
	pos[1] = 2;

	/*
	 * Only one Beacon Report Measurement is supported at a time, so
	 * the Beacon Report ID can always be set to 1.
	 */
	pos[2] = 1;

	/* Fragment ID Number (bits 0..6) and More Frame Body Fragments (bit 7)
 */
	pos[3] = idx;
	if (data->report_detail != BEACON_REPORT_DETAIL_NONE && *ie_len)
		pos[3] |= REPORTED_FRAME_BODY_MORE_FRAGMENTS;
	else
		pos[3] &= ~REPORTED_FRAME_BODY_MORE_FRAGMENTS;

	pos += REPORTED_FRAME_BODY_SUBELEM_LEN;

	if (data->last_indication) {
		pos[0] = WLAN_BEACON_REPORT_SUBELEM_LAST_INDICATION;
		pos[1] = 1;

		/* This field will be updated later if this is the last frame */
		pos[2] = 0;
	}

	ret = wpas_rrm_report_elem(wpa_buf, data->token,
				   MEASUREMENT_REPORT_MODE_ACCEPT,
				   MEASURE_TYPE_BEACON, buf,
				   ret + sizeof(*rep) + subelems_len);
out:
	os_free(buf);
	return ret;
}