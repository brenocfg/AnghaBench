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
struct wpa_sm {unsigned int dot11RSNAConfigPMKLifetime; unsigned int dot11RSNAConfigPMKReauthThreshold; unsigned int dot11RSNAConfigSATimeout; unsigned int proto; unsigned int pairwise_cipher; unsigned int group_cipher; unsigned int key_mgmt; unsigned int mgmt_group_cipher; unsigned int rsn_enabled; unsigned int mfp; unsigned int ocv; } ;
typedef  enum wpa_sm_conf_params { ____Placeholder_wpa_sm_conf_params } wpa_sm_conf_params ;

/* Variables and functions */
#define  RSNA_PMK_LIFETIME 138 
#define  RSNA_PMK_REAUTH_THRESHOLD 137 
#define  RSNA_SA_TIMEOUT 136 
#define  WPA_PARAM_GROUP 135 
#define  WPA_PARAM_KEY_MGMT 134 
#define  WPA_PARAM_MFP 133 
#define  WPA_PARAM_MGMT_GROUP 132 
#define  WPA_PARAM_OCV 131 
#define  WPA_PARAM_PAIRWISE 130 
#define  WPA_PARAM_PROTO 129 
#define  WPA_PARAM_RSN_ENABLED 128 

int wpa_sm_set_param(struct wpa_sm *sm, enum wpa_sm_conf_params param,
		     unsigned int value)
{
	int ret = 0;

	if (sm == NULL)
		return -1;

	switch (param) {
	case RSNA_PMK_LIFETIME:
		if (value > 0)
			sm->dot11RSNAConfigPMKLifetime = value;
		else
			ret = -1;
		break;
	case RSNA_PMK_REAUTH_THRESHOLD:
		if (value > 0 && value <= 100)
			sm->dot11RSNAConfigPMKReauthThreshold = value;
		else
			ret = -1;
		break;
	case RSNA_SA_TIMEOUT:
		if (value > 0)
			sm->dot11RSNAConfigSATimeout = value;
		else
			ret = -1;
		break;
	case WPA_PARAM_PROTO:
		sm->proto = value;
		break;
	case WPA_PARAM_PAIRWISE:
		sm->pairwise_cipher = value;
		break;
	case WPA_PARAM_GROUP:
		sm->group_cipher = value;
		break;
	case WPA_PARAM_KEY_MGMT:
		sm->key_mgmt = value;
		break;
#ifdef CONFIG_IEEE80211W
	case WPA_PARAM_MGMT_GROUP:
		sm->mgmt_group_cipher = value;
		break;
#endif /* CONFIG_IEEE80211W */
	case WPA_PARAM_RSN_ENABLED:
		sm->rsn_enabled = value;
		break;
	case WPA_PARAM_MFP:
		sm->mfp = value;
		break;
	case WPA_PARAM_OCV:
		sm->ocv = value;
		break;
	default:
		break;
	}

	return ret;
}