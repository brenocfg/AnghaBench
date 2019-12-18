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
typedef  int u8 ;
struct ieee80211req_wpaie {int* wpa_ie; int /*<<< orphan*/  wpa_macaddr; } ;
typedef  int /*<<< orphan*/  ie ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_IOC_WPAIE ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  drv_event_assoc (void*,int*,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get80211var (void*,int /*<<< orphan*/ ,struct ieee80211req_wpaie*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211req_wpaie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
bsd_new_sta(void *priv, void *ctx, u8 addr[IEEE80211_ADDR_LEN])
{
	struct ieee80211req_wpaie ie;
	int ielen = 0;
	u8 *iebuf = NULL;

	/*
	 * Fetch and validate any negotiated WPA/RSN parameters.
	 */
	memset(&ie, 0, sizeof(ie));
	memcpy(ie.wpa_macaddr, addr, IEEE80211_ADDR_LEN);
	if (get80211var(priv, IEEE80211_IOC_WPAIE, &ie, sizeof(ie)) < 0) {
		wpa_printf(MSG_INFO,
			   "Failed to get WPA/RSN information element");
		goto no_ie;
	}
	iebuf = ie.wpa_ie;
	ielen = ie.wpa_ie[1];
	if (ielen == 0)
		iebuf = NULL;
	else
		ielen += 2;

no_ie:
	drv_event_assoc(ctx, addr, iebuf, ielen, 0);
}