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
struct wpa_authenticator {int /*<<< orphan*/  pmksa; } ;
struct rsn_pmksa_cache_entry {int dummy; } ;

/* Variables and functions */
 struct rsn_pmksa_cache_entry* pmksa_cache_auth_get (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

struct rsn_pmksa_cache_entry *
wpa_auth_pmksa_get(struct wpa_authenticator *wpa_auth, const u8 *sta_addr,
		   const u8 *pmkid)
{
	if (!wpa_auth || !wpa_auth->pmksa)
		return NULL;
	return pmksa_cache_auth_get(wpa_auth->pmksa, sta_addr, pmkid);
}