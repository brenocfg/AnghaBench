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
struct hostapd_iface {TYPE_1__* conf; TYPE_2__* current_mode; } ;
struct TYPE_4__ {scalar_t__ mode; } ;
struct TYPE_3__ {int ht_capab; scalar_t__ ieee80211ac; scalar_t__ ieee80211ax; int /*<<< orphan*/  ieee80211n; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211B ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int HT_CAP_INFO_DSSS_CCK40MHZ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  ieee80211ac_supported_vht_capab (struct hostapd_iface*) ; 
 int /*<<< orphan*/  ieee80211ax_supported_he_capab (struct hostapd_iface*) ; 
 int /*<<< orphan*/  ieee80211n_allowed_ht40_channel_pair (struct hostapd_iface*) ; 
 int ieee80211n_check_40mhz (struct hostapd_iface*) ; 
 int /*<<< orphan*/  ieee80211n_supported_ht_capab (struct hostapd_iface*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int hostapd_check_ht_capab(struct hostapd_iface *iface)
{
#ifdef CONFIG_IEEE80211N
	int ret;
	if (!iface->conf->ieee80211n)
		return 0;

	if (iface->current_mode->mode != HOSTAPD_MODE_IEEE80211B &&
	    iface->current_mode->mode != HOSTAPD_MODE_IEEE80211G &&
	    (iface->conf->ht_capab & HT_CAP_INFO_DSSS_CCK40MHZ)) {
		wpa_printf(MSG_DEBUG,
			   "Disable HT capability [DSSS_CCK-40] on 5 GHz band");
		iface->conf->ht_capab &= ~HT_CAP_INFO_DSSS_CCK40MHZ;
	}

	if (!ieee80211n_supported_ht_capab(iface))
		return -1;
#ifdef CONFIG_IEEE80211AX
	if (iface->conf->ieee80211ax &&
	    !ieee80211ax_supported_he_capab(iface))
		return -1;
#endif /* CONFIG_IEEE80211AX */
#ifdef CONFIG_IEEE80211AC
	if (iface->conf->ieee80211ac &&
	    !ieee80211ac_supported_vht_capab(iface))
		return -1;
#endif /* CONFIG_IEEE80211AC */
	ret = ieee80211n_check_40mhz(iface);
	if (ret)
		return ret;
	if (!ieee80211n_allowed_ht40_channel_pair(iface))
		return -1;
#endif /* CONFIG_IEEE80211N */

	return 0;
}