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
typedef  int uint8_t ;
struct ieee80211_ies {int* data; int len; int* wpa_ie; int* wme_ie; int* ath_ie; int* tdma_ie; int* rsn_ie; int* htcap_ie; int* htinfo_ie; int* meshid_ie; int* vhtcap_ie; int* vhtopmode_ie; int* vhtpwrenv_ie; int* bssload_ie; int* apchanrep_ie; } ;

/* Variables and functions */
#define  IEEE80211_ELEMID_APCHANREP 137 
#define  IEEE80211_ELEMID_BSSLOAD 136 
#define  IEEE80211_ELEMID_HTCAP 135 
#define  IEEE80211_ELEMID_HTINFO 134 
#define  IEEE80211_ELEMID_MESHID 133 
#define  IEEE80211_ELEMID_RSN 132 
#define  IEEE80211_ELEMID_VENDOR 131 
#define  IEEE80211_ELEMID_VHT_CAP 130 
#define  IEEE80211_ELEMID_VHT_OPMODE 129 
#define  IEEE80211_ELEMID_VHT_PWR_ENV 128 
 int /*<<< orphan*/  isatherosoui (int*) ; 
 int /*<<< orphan*/  istdmaoui (int*) ; 
 int /*<<< orphan*/  iswmeoui (int*) ; 
 int /*<<< orphan*/  iswpaoui (int*) ; 

void
ieee80211_ies_expand(struct ieee80211_ies *ies)
{
	uint8_t *ie;
	int ielen;

	ie = ies->data;
	ielen = ies->len;
	while (ielen > 0) {
		switch (ie[0]) {
		case IEEE80211_ELEMID_VENDOR:
			if (iswpaoui(ie))
				ies->wpa_ie = ie;
			else if (iswmeoui(ie))
				ies->wme_ie = ie;
#ifdef IEEE80211_SUPPORT_SUPERG
			else if (isatherosoui(ie))
				ies->ath_ie = ie;
#endif
#ifdef IEEE80211_SUPPORT_TDMA
			else if (istdmaoui(ie))
				ies->tdma_ie = ie;
#endif
			break;
		case IEEE80211_ELEMID_RSN:
			ies->rsn_ie = ie;
			break;
		case IEEE80211_ELEMID_HTCAP:
			ies->htcap_ie = ie;
			break;
		case IEEE80211_ELEMID_HTINFO:
			ies->htinfo_ie = ie;
			break;
#ifdef IEEE80211_SUPPORT_MESH
		case IEEE80211_ELEMID_MESHID:
			ies->meshid_ie = ie;
			break;
#endif
		case IEEE80211_ELEMID_VHT_CAP:
			ies->vhtcap_ie = ie;
			break;
		case IEEE80211_ELEMID_VHT_OPMODE:
			ies->vhtopmode_ie = ie;
			break;
		case IEEE80211_ELEMID_VHT_PWR_ENV:
			ies->vhtpwrenv_ie = ie;
			break;
		case IEEE80211_ELEMID_BSSLOAD:
			ies->bssload_ie = ie;
			break;
		case IEEE80211_ELEMID_APCHANREP:
			ies->apchanrep_ie = ie;
			break;
		}
		ielen -= 2 + ie[1];
		ie += 2 + ie[1];
	}
}