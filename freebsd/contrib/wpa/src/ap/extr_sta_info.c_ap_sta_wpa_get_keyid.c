#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int /*<<< orphan*/  wpa_sm; } ;
struct hostapd_wpa_psk {char const* keyid; int /*<<< orphan*/  psk; struct hostapd_wpa_psk* next; } ;
struct hostapd_ssid {struct hostapd_wpa_psk* wpa_psk; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {struct hostapd_ssid ssid; } ;

/* Variables and functions */
 int PMK_LEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * wpa_auth_get_pmk (int /*<<< orphan*/ ,int*) ; 

const char * ap_sta_wpa_get_keyid(struct hostapd_data *hapd,
				  struct sta_info *sta)
{
	struct hostapd_wpa_psk *psk;
	struct hostapd_ssid *ssid;
	const u8 *pmk;
	int pmk_len;

	ssid = &hapd->conf->ssid;

	pmk = wpa_auth_get_pmk(sta->wpa_sm, &pmk_len);
	if (!pmk || pmk_len != PMK_LEN)
		return NULL;

	for (psk = ssid->wpa_psk; psk; psk = psk->next)
		if (os_memcmp(pmk, psk->psk, PMK_LEN) == 0)
			break;
	if (!psk)
		return NULL;
	if (!psk || !psk->keyid[0])
		return NULL;

	return psk->keyid;
}