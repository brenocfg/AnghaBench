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
struct iwi_softc {int dummy; } ;
struct ieee80211_wme_info {int wme_len; int* wme_oui; scalar_t__ wme_info; int /*<<< orphan*/  wme_version; int /*<<< orphan*/  wme_subtype; int /*<<< orphan*/  wme_type; int /*<<< orphan*/  wme_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IEEE80211_ELEMID_VENDOR ; 
 int /*<<< orphan*/  IWI_CMD_SET_WMEIE ; 
 int /*<<< orphan*/  WME_INFO_OUI_SUBTYPE ; 
 int /*<<< orphan*/  WME_OUI_TYPE ; 
 int /*<<< orphan*/  WME_VERSION ; 
 int iwi_cmd (struct iwi_softc*,int /*<<< orphan*/ ,struct ieee80211_wme_info*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_wme_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwi_wme_setie(struct iwi_softc *sc)
{
	struct ieee80211_wme_info wme;

	memset(&wme, 0, sizeof wme);
	wme.wme_id = IEEE80211_ELEMID_VENDOR;
	wme.wme_len = sizeof (struct ieee80211_wme_info) - 2;
	wme.wme_oui[0] = 0x00;
	wme.wme_oui[1] = 0x50;
	wme.wme_oui[2] = 0xf2;
	wme.wme_type = WME_OUI_TYPE;
	wme.wme_subtype = WME_INFO_OUI_SUBTYPE;
	wme.wme_version = WME_VERSION;
	wme.wme_info = 0;

	DPRINTF(("Setting WME IE (len=%u)\n", wme.wme_len));
	return iwi_cmd(sc, IWI_CMD_SET_WMEIE, &wme, sizeof wme);
}