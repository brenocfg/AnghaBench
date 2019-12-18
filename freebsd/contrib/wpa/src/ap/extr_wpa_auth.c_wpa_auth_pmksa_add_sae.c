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
struct TYPE_2__ {scalar_t__ disable_pmksa_caching; } ;
struct wpa_authenticator {int /*<<< orphan*/  addr; int /*<<< orphan*/  pmksa; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PMK_LEN ; 
 int /*<<< orphan*/  WPA_KEY_MGMT_SAE ; 
 scalar_t__ pmksa_cache_auth_add (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int wpa_auth_pmksa_add_sae(struct wpa_authenticator *wpa_auth, const u8 *addr,
			   const u8 *pmk, const u8 *pmkid)
{
	if (wpa_auth->conf.disable_pmksa_caching)
		return -1;

	wpa_hexdump_key(MSG_DEBUG, "RSN: Cache PMK from SAE", pmk, PMK_LEN);
	if (pmksa_cache_auth_add(wpa_auth->pmksa, pmk, PMK_LEN, pmkid,
				 NULL, 0,
				 wpa_auth->addr, addr, 0, NULL,
				 WPA_KEY_MGMT_SAE))
		return 0;

	return -1;
}