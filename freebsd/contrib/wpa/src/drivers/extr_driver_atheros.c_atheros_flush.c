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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_REASON_AUTH_LEAVE ; 
 int atheros_sta_deauth (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
atheros_flush(void *priv)
{
	u8 allsta[IEEE80211_ADDR_LEN];
	os_memset(allsta, 0xff, IEEE80211_ADDR_LEN);
	return atheros_sta_deauth(priv, NULL, allsta,
				  IEEE80211_REASON_AUTH_LEAVE);
}