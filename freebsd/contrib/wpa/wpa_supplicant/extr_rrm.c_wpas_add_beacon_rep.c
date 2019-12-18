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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  duration; } ;
struct beacon_rep_data {scalar_t__ ssid_len; scalar_t__ report_detail; TYPE_1__ scan_params; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
struct wpa_supplicant {struct beacon_rep_data beacon_rep_data; } ;
struct wpa_bss {size_t ie_len; size_t beacon_ie_len; scalar_t__ ssid_len; int /*<<< orphan*/  bssid; int /*<<< orphan*/  level; int /*<<< orphan*/  freq; int /*<<< orphan*/  ssid; } ;
struct rrm_measurement_beacon_report {int rsni; int /*<<< orphan*/  parent_tsf; scalar_t__ antenna_id; int /*<<< orphan*/  bssid; int /*<<< orphan*/  rcpi; int /*<<< orphan*/  duration; int /*<<< orphan*/  start_time; int /*<<< orphan*/  report_info; int /*<<< orphan*/  channel; int /*<<< orphan*/  op_class; } ;

/* Variables and functions */
 scalar_t__ BEACON_REPORT_DETAIL_NONE ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  broadcast_ether_addr ; 
 int /*<<< orphan*/  host_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rssi_to_rcpi (int /*<<< orphan*/ ) ; 
 int wpas_add_beacon_rep_elem (struct beacon_rep_data*,struct wpa_bss*,struct wpabuf**,struct rrm_measurement_beacon_report*,scalar_t__**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpas_get_op_chan_phy (int /*<<< orphan*/ ,scalar_t__*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wpas_add_beacon_rep(struct wpa_supplicant *wpa_s,
			       struct wpabuf **wpa_buf, struct wpa_bss *bss,
			       u64 start, u64 parent_tsf)
{
	struct beacon_rep_data *data = &wpa_s->beacon_rep_data;
	u8 *ies = (u8 *) (bss + 1);
	u8 *pos = ies;
	size_t ies_len = bss->ie_len ? bss->ie_len : bss->beacon_ie_len;
	struct rrm_measurement_beacon_report rep;
	u8 idx = 0;

	if (os_memcmp(data->bssid, broadcast_ether_addr, ETH_ALEN) != 0 &&
	    os_memcmp(data->bssid, bss->bssid, ETH_ALEN) != 0)
		return 0;

	if (data->ssid_len &&
	    (data->ssid_len != bss->ssid_len ||
	     os_memcmp(data->ssid, bss->ssid, bss->ssid_len) != 0))
		return 0;

	if (wpas_get_op_chan_phy(bss->freq, ies, ies_len, &rep.op_class,
				 &rep.channel, &rep.report_info) < 0)
		return 0;

	rep.start_time = host_to_le64(start);
	rep.duration = host_to_le16(data->scan_params.duration);
	rep.rcpi = rssi_to_rcpi(bss->level);
	rep.rsni = 255; /* 255 indicates that RSNI is not available */
	os_memcpy(rep.bssid, bss->bssid, ETH_ALEN);
	rep.antenna_id = 0; /* unknown */
	rep.parent_tsf = host_to_le32(parent_tsf);

	do {
		int ret;

		ret = wpas_add_beacon_rep_elem(data, bss, wpa_buf, &rep,
					       &pos, &ies_len, idx++);
		if (ret)
			return ret;
	} while (data->report_detail != BEACON_REPORT_DETAIL_NONE &&
		 ies_len >= 2);

	return 0;
}