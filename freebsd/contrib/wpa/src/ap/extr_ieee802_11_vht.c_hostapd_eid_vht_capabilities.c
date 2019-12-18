#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ieee80211_vht_capabilities {int /*<<< orphan*/  vht_supported_mcs_set; int /*<<< orphan*/  vht_capabilities_info; } ;
struct hostapd_hw_modes {scalar_t__ mode; scalar_t__ vht_capab; int /*<<< orphan*/  vht_mcs_set; } ;
struct hostapd_data {TYPE_3__* iface; TYPE_1__* conf; } ;
struct TYPE_6__ {int num_hw_features; TYPE_2__* conf; struct hostapd_hw_modes* hw_features; struct hostapd_hw_modes* current_mode; } ;
struct TYPE_5__ {int vht_capab; } ;
struct TYPE_4__ {scalar_t__ vendor_vht; } ;

/* Variables and functions */
 scalar_t__ HOSTAPD_MODE_IEEE80211A ; 
 scalar_t__ HOSTAPD_MODE_IEEE80211G ; 
 int VHT_CAP_BEAMFORMEE_STS_OFFSET ; 
 int /*<<< orphan*/  WLAN_EID_VHT_CAP ; 
 int /*<<< orphan*/  host_to_le32 (int) ; 
 int le_to_host32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memset (struct ieee80211_vht_capabilities*,int /*<<< orphan*/ ,int) ; 

u8 * hostapd_eid_vht_capabilities(struct hostapd_data *hapd, u8 *eid, u32 nsts)
{
	struct ieee80211_vht_capabilities *cap;
	struct hostapd_hw_modes *mode = hapd->iface->current_mode;
	u8 *pos = eid;

	if (!mode)
		return eid;

	if (mode->mode == HOSTAPD_MODE_IEEE80211G && hapd->conf->vendor_vht &&
	    mode->vht_capab == 0 && hapd->iface->hw_features) {
		int i;

		for (i = 0; i < hapd->iface->num_hw_features; i++) {
			if (hapd->iface->hw_features[i].mode ==
			    HOSTAPD_MODE_IEEE80211A) {
				mode = &hapd->iface->hw_features[i];
				break;
			}
		}
	}

	*pos++ = WLAN_EID_VHT_CAP;
	*pos++ = sizeof(*cap);

	cap = (struct ieee80211_vht_capabilities *) pos;
	os_memset(cap, 0, sizeof(*cap));
	cap->vht_capabilities_info = host_to_le32(
		hapd->iface->conf->vht_capab);

	if (nsts != 0) {
		u32 hapd_nsts;

		hapd_nsts = le_to_host32(cap->vht_capabilities_info);
		hapd_nsts = (hapd_nsts >> VHT_CAP_BEAMFORMEE_STS_OFFSET) & 7;
		cap->vht_capabilities_info &=
			~(host_to_le32(hapd_nsts <<
				       VHT_CAP_BEAMFORMEE_STS_OFFSET));
		cap->vht_capabilities_info |=
			host_to_le32(nsts << VHT_CAP_BEAMFORMEE_STS_OFFSET);
	}

	/* Supported MCS set comes from hw */
	os_memcpy(&cap->vht_supported_mcs_set, mode->vht_mcs_set, 8);

	pos += sizeof(*cap);

	return pos;
}