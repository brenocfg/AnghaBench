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
struct wpa_supplicant {int dummy; } ;
struct neighbor_report {int regulatory_class; int channel_number; int phy_type; int /*<<< orphan*/  freq; int /*<<< orphan*/  bssid_info; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_GET_LE32 (int const*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  wnm_nei_get_chan (struct wpa_supplicant*,int,int) ; 
 int /*<<< orphan*/  wnm_parse_neighbor_report_elem (struct neighbor_report*,int,int,int const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wnm_parse_neighbor_report(struct wpa_supplicant *wpa_s,
				      const u8 *pos, u8 len,
				      struct neighbor_report *rep)
{
	u8 left = len;

	if (left < 13) {
		wpa_printf(MSG_DEBUG, "WNM: Too short neighbor report");
		return;
	}

	os_memcpy(rep->bssid, pos, ETH_ALEN);
	rep->bssid_info = WPA_GET_LE32(pos + ETH_ALEN);
	rep->regulatory_class = *(pos + 10);
	rep->channel_number = *(pos + 11);
	rep->phy_type = *(pos + 12);

	pos += 13;
	left -= 13;

	while (left >= 2) {
		u8 id, elen;

		id = *pos++;
		elen = *pos++;
		wpa_printf(MSG_DEBUG, "WNM: Subelement id=%u len=%u", id, elen);
		left -= 2;
		if (elen > left) {
			wpa_printf(MSG_DEBUG,
				   "WNM: Truncated neighbor report subelement");
			break;
		}
		wnm_parse_neighbor_report_elem(rep, id, elen, pos);
		left -= elen;
		pos += elen;
	}

	rep->freq = wnm_nei_get_chan(wpa_s, rep->regulatory_class,
				     rep->channel_number);
}