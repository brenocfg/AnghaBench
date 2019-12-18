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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct wpa_supplicant {int dummy; } ;
struct wpa_cred {unsigned int min_dl_bandwidth_home; unsigned int min_ul_bandwidth_home; unsigned int min_dl_bandwidth_roaming; unsigned int min_ul_bandwidth_roaming; } ;
struct wpa_bss {TYPE_1__* anqp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * domain_name; int /*<<< orphan*/ * hs20_wan_metrics; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ WPA_GET_LE16 (int const*) ; 
 int WPA_GET_LE32 (int const*) ; 
 int interworking_home_sp_cred (struct wpa_supplicant*,struct wpa_cred*,int /*<<< orphan*/ *) ; 
 int* wpabuf_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cred_below_min_backhaul(struct wpa_supplicant *wpa_s,
				   struct wpa_cred *cred, struct wpa_bss *bss)
{
#ifdef CONFIG_HS20
	int res;
	unsigned int dl_bandwidth, ul_bandwidth;
	const u8 *wan;
	u8 wan_info, dl_load, ul_load;
	u16 lmd;
	u32 ul_speed, dl_speed;

	if (!cred->min_dl_bandwidth_home &&
	    !cred->min_ul_bandwidth_home &&
	    !cred->min_dl_bandwidth_roaming &&
	    !cred->min_ul_bandwidth_roaming)
		return 0; /* No bandwidth constraint specified */

	if (bss->anqp == NULL || bss->anqp->hs20_wan_metrics == NULL)
		return 0; /* No WAN Metrics known - ignore constraint */

	wan = wpabuf_head(bss->anqp->hs20_wan_metrics);
	wan_info = wan[0];
	if (wan_info & BIT(3))
		return 1; /* WAN link at capacity */
	lmd = WPA_GET_LE16(wan + 11);
	if (lmd == 0)
		return 0; /* Downlink/Uplink Load was not measured */
	dl_speed = WPA_GET_LE32(wan + 1);
	ul_speed = WPA_GET_LE32(wan + 5);
	dl_load = wan[9];
	ul_load = wan[10];

	if (dl_speed >= 0xffffff)
		dl_bandwidth = dl_speed / 255 * (255 - dl_load);
	else
		dl_bandwidth = dl_speed * (255 - dl_load) / 255;

	if (ul_speed >= 0xffffff)
		ul_bandwidth = ul_speed / 255 * (255 - ul_load);
	else
		ul_bandwidth = ul_speed * (255 - ul_load) / 255;

	res = interworking_home_sp_cred(wpa_s, cred, bss->anqp ?
					bss->anqp->domain_name : NULL);
	if (res > 0) {
		if (cred->min_dl_bandwidth_home > dl_bandwidth)
			return 1;
		if (cred->min_ul_bandwidth_home > ul_bandwidth)
			return 1;
	} else {
		if (cred->min_dl_bandwidth_roaming > dl_bandwidth)
			return 1;
		if (cred->min_ul_bandwidth_roaming > ul_bandwidth)
			return 1;
	}
#endif /* CONFIG_HS20 */

	return 0;
}