#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hostapd_data {TYPE_4__* conf; TYPE_2__* iface; TYPE_1__* iconf; } ;
struct TYPE_7__ {int /*<<< orphan*/  utf8_ssid; } ;
struct TYPE_8__ {int time_advertisement; int tdls; int wpa; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  ftm_initiator; int /*<<< orphan*/  ftm_responder; TYPE_3__ ssid; int /*<<< orphan*/  mbo_enabled; int /*<<< orphan*/  hs20; int /*<<< orphan*/  qos_map_set_len; int /*<<< orphan*/  interworking; int /*<<< orphan*/  bss_transition; int /*<<< orphan*/  wnm_sleep_mode; int /*<<< orphan*/  coloc_intf_reporting; int /*<<< orphan*/  proxy_arp; } ;
struct TYPE_6__ {int drv_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  obss_interval; } ;

/* Variables and functions */
 int TDLS_PROHIBIT ; 
 int TDLS_PROHIBIT_CHAN_SWITCH ; 
 int WPA_DRIVER_FLAGS_AP_CSA ; 
 int WPA_PROTO_RSN ; 
 int hostapd_sae_pw_id_in_use (TYPE_4__*) ; 
 int /*<<< orphan*/  wpa_key_mgmt_fils (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_key_mgmt_sae (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_ext_capab_byte(struct hostapd_data *hapd, u8 *pos, int idx)
{
	*pos = 0x00;

	switch (idx) {
	case 0: /* Bits 0-7 */
		if (hapd->iconf->obss_interval)
			*pos |= 0x01; /* Bit 0 - Coexistence management */
		if (hapd->iface->drv_flags & WPA_DRIVER_FLAGS_AP_CSA)
			*pos |= 0x04; /* Bit 2 - Extended Channel Switching */
		break;
	case 1: /* Bits 8-15 */
		if (hapd->conf->proxy_arp)
			*pos |= 0x10; /* Bit 12 - Proxy ARP */
		if (hapd->conf->coloc_intf_reporting) {
			/* Bit 13 - Collocated Interference Reporting */
			*pos |= 0x20;
		}
		break;
	case 2: /* Bits 16-23 */
		if (hapd->conf->wnm_sleep_mode)
			*pos |= 0x02; /* Bit 17 - WNM-Sleep Mode */
		if (hapd->conf->bss_transition)
			*pos |= 0x08; /* Bit 19 - BSS Transition */
		break;
	case 3: /* Bits 24-31 */
#ifdef CONFIG_WNM_AP
		*pos |= 0x02; /* Bit 25 - SSID List */
#endif /* CONFIG_WNM_AP */
		if (hapd->conf->time_advertisement == 2)
			*pos |= 0x08; /* Bit 27 - UTC TSF Offset */
		if (hapd->conf->interworking)
			*pos |= 0x80; /* Bit 31 - Interworking */
		break;
	case 4: /* Bits 32-39 */
		if (hapd->conf->qos_map_set_len)
			*pos |= 0x01; /* Bit 32 - QoS Map */
		if (hapd->conf->tdls & TDLS_PROHIBIT)
			*pos |= 0x40; /* Bit 38 - TDLS Prohibited */
		if (hapd->conf->tdls & TDLS_PROHIBIT_CHAN_SWITCH) {
			/* Bit 39 - TDLS Channel Switching Prohibited */
			*pos |= 0x80;
		}
		break;
	case 5: /* Bits 40-47 */
#ifdef CONFIG_HS20
		if (hapd->conf->hs20)
			*pos |= 0x40; /* Bit 46 - WNM-Notification */
#endif /* CONFIG_HS20 */
#ifdef CONFIG_MBO
		if (hapd->conf->mbo_enabled)
			*pos |= 0x40; /* Bit 46 - WNM-Notification */
#endif /* CONFIG_MBO */
		break;
	case 6: /* Bits 48-55 */
		if (hapd->conf->ssid.utf8_ssid)
			*pos |= 0x01; /* Bit 48 - UTF-8 SSID */
		break;
	case 7: /* Bits 56-63 */
		break;
	case 8: /* Bits 64-71 */
		if (hapd->conf->ftm_responder)
			*pos |= 0x40; /* Bit 70 - FTM responder */
		if (hapd->conf->ftm_initiator)
			*pos |= 0x80; /* Bit 71 - FTM initiator */
		break;
	case 9: /* Bits 72-79 */
#ifdef CONFIG_FILS
		if ((hapd->conf->wpa & WPA_PROTO_RSN) &&
		    wpa_key_mgmt_fils(hapd->conf->wpa_key_mgmt))
			*pos |= 0x01;
#endif /* CONFIG_FILS */
		break;
	case 10: /* Bits 80-87 */
#ifdef CONFIG_SAE
		if (hapd->conf->wpa &&
		    wpa_key_mgmt_sae(hapd->conf->wpa_key_mgmt)) {
			int in_use = hostapd_sae_pw_id_in_use(hapd->conf);

			if (in_use)
				*pos |= 0x02; /* Bit 81 - SAE Password
					       * Identifiers In Use */
			if (in_use == 2)
				*pos |= 0x04; /* Bit 82 - SAE Password
					       * Identifiers Used Exclusively */
		}
#endif /* CONFIG_SAE */
		break;
	}
}