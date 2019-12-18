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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MLME_DEAUTH ; 
 int bsd_send_mlme_param (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
wpa_driver_bsd_deauthenticate(void *priv, const u8 *addr, u16 reason_code)
{
	return bsd_send_mlme_param(priv, IEEE80211_MLME_DEAUTH, reason_code,
				   addr);
}