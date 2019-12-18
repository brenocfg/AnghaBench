#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee802_11_elems {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  variable; } ;
struct TYPE_4__ {TYPE_1__ beacon; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;
struct hostapd_frame_info {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int IEEE80211_HDRLEN ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  ap_list_process_beacon (int /*<<< orphan*/ ,struct ieee80211_mgmt const*,struct ieee802_11_elems*,struct hostapd_frame_info*) ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (int /*<<< orphan*/ ,size_t,struct ieee802_11_elems*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void handle_beacon(struct hostapd_data *hapd,
			  const struct ieee80211_mgmt *mgmt, size_t len,
			  struct hostapd_frame_info *fi)
{
	struct ieee802_11_elems elems;

	if (len < IEEE80211_HDRLEN + sizeof(mgmt->u.beacon)) {
		wpa_printf(MSG_INFO, "handle_beacon - too short payload (len=%lu)",
			   (unsigned long) len);
		return;
	}

	(void) ieee802_11_parse_elems(mgmt->u.beacon.variable,
				      len - (IEEE80211_HDRLEN +
					     sizeof(mgmt->u.beacon)), &elems,
				      0);

	ap_list_process_beacon(hapd->iface, mgmt, &elems, fi);
}