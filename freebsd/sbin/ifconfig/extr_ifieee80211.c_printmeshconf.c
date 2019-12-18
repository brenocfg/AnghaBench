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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211_meshconf_ie {scalar_t__ conf_pselid; scalar_t__ conf_pmetid; scalar_t__ conf_ccid; scalar_t__ conf_syncid; scalar_t__ conf_authid; int conf_form; int conf_cap; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_MESHCONF_AUTH_DISABLED ; 
 scalar_t__ IEEE80211_MESHCONF_CC_DISABLED ; 
 scalar_t__ IEEE80211_MESHCONF_METRIC_AIRTIME ; 
 scalar_t__ IEEE80211_MESHCONF_PATH_HWMP ; 
 scalar_t__ IEEE80211_MESHCONF_SYNC_NEIGHOFF ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
printmeshconf(const char *tag, const uint8_t *ie, size_t ielen, int maxlen)
{

	printf("%s", tag);
	if (verbose) {
		const struct ieee80211_meshconf_ie *mconf =
			(const struct ieee80211_meshconf_ie *)ie;
		printf("<PATH:");
		if (mconf->conf_pselid == IEEE80211_MESHCONF_PATH_HWMP)
			printf("HWMP");
		else
			printf("UNKNOWN");
		printf(" LINK:");
		if (mconf->conf_pmetid == IEEE80211_MESHCONF_METRIC_AIRTIME)
			printf("AIRTIME");
		else
			printf("UNKNOWN");
		printf(" CONGESTION:");
		if (mconf->conf_ccid == IEEE80211_MESHCONF_CC_DISABLED)
			printf("DISABLED");
		else
			printf("UNKNOWN");
		printf(" SYNC:");
		if (mconf->conf_syncid == IEEE80211_MESHCONF_SYNC_NEIGHOFF)
			printf("NEIGHOFF");
		else
			printf("UNKNOWN");
		printf(" AUTH:");
		if (mconf->conf_authid == IEEE80211_MESHCONF_AUTH_DISABLED)
			printf("DISABLED");
		else
			printf("UNKNOWN");
		printf(" FORM:0x%x CAPS:0x%x>", mconf->conf_form,
		    mconf->conf_cap);
	}
}