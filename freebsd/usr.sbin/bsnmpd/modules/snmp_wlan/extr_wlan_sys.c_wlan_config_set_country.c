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
typedef  size_t uint32_t ;
struct wlan_iface {int nchannels; char* country_code; int /*<<< orphan*/  reg_domain; int /*<<< orphan*/  state; int /*<<< orphan*/  wname; int /*<<< orphan*/  chanlist; } ;
struct TYPE_5__ {char* isocc; char location; int /*<<< orphan*/  regdomain; } ;
struct TYPE_4__ {int ic_nchans; TYPE_3__* ic_chans; } ;
struct ieee80211_regdomain_req {TYPE_2__ rd; TYPE_1__ chaninfo; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_6__ {int ic_maxregpower; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_IOC_REGDOMAIN ; 
 int /*<<< orphan*/  IEEE80211_IOC_TXPOWMAX ; 
 size_t IEEE80211_REGDOMAIN_SIZE (int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  free (struct ieee80211_regdomain_req*) ; 
 struct ieee80211_regdomain_req* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_regdomain_req*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlanIfaceState_down ; 
 int /*<<< orphan*/  wlanIfaceState_up ; 
 scalar_t__ wlan_config_state (struct wlan_iface*,int) ; 
 scalar_t__ wlan_get_channel_list (struct wlan_iface*) ; 
 scalar_t__ wlan_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct ieee80211_regdomain_req*,size_t*,int) ; 
 int /*<<< orphan*/  wlan_regdomain_to_snmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlan_snmp_to_regdomain (int) ; 

__attribute__((used)) static int
wlan_config_set_country(struct wlan_iface *wif, char *ccode, int rdomain)
{
	int val = 0, txpowermax;
	uint32_t i;
	size_t argsize = 0;
	struct ieee80211_regdomain_req *regdomain;

	if (wlan_get_channel_list(wif) < 0)
		return (-1);

	if (wif->nchannels == 0) {
		syslog(LOG_ERR, "iface %s - set regdomain failed", wif->wname);
		return (-1);
	}

	if (wlan_ioctl(wif->wname, IEEE80211_IOC_TXPOWMAX, &txpowermax, 0,
	    &argsize, 0) < 0)
		return (-1);

	regdomain = malloc(IEEE80211_REGDOMAIN_SIZE(wif->nchannels));
	if (regdomain == NULL)
		return (-1);
	memset(regdomain, 0, IEEE80211_REGDOMAIN_SIZE(wif->nchannels));
	argsize = IEEE80211_REGDOMAIN_SIZE(wif->nchannels);

	/* XXX: recheck with how this is done by ifconfig(8) */
	regdomain->rd.regdomain = wlan_snmp_to_regdomain(rdomain);
	regdomain->rd.isocc[0] = ccode[0];
	regdomain->rd.isocc[1] = ccode[1];
	regdomain->rd.location = ccode[2];

	/* XXX: fill the channel list properly */
	regdomain->chaninfo.ic_nchans = wif->nchannels;
	memcpy(regdomain->chaninfo.ic_chans, wif->chanlist,
	    wif->nchannels * sizeof(struct ieee80211_channel));
	for (i = 0; i < wif->nchannels; i++)
		regdomain->chaninfo.ic_chans[i].ic_maxregpower = txpowermax;

	wif->state = wlanIfaceState_down;
	if (wlan_config_state(wif, 1) < 0 ||
	    wlan_ioctl(wif->wname, IEEE80211_IOC_REGDOMAIN, &val, regdomain,
	    &argsize, 1) < 0) {
		free(regdomain);
		return (-1);
	}

	wif->state = wlanIfaceState_up;
	(void)wlan_config_state(wif, 1);
	wif->reg_domain = wlan_regdomain_to_snmp(regdomain->rd.regdomain);
	wif->country_code[0] = regdomain->rd.isocc[0];
	wif->country_code[1] = regdomain->rd.isocc[1];
	wif->country_code[2] = regdomain->rd.location;
	free(regdomain);

	return (0);
}