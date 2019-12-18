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
struct wpa_group {struct wpa_group* next; struct wpa_group* group; struct wpa_group* wpa_ie; int /*<<< orphan*/  ip_pool; int /*<<< orphan*/ * ft_pmk_cache; int /*<<< orphan*/  pmksa; } ;
struct wpa_authenticator {struct wpa_authenticator* next; struct wpa_authenticator* group; struct wpa_authenticator* wpa_ie; int /*<<< orphan*/  ip_pool; int /*<<< orphan*/ * ft_pmk_cache; int /*<<< orphan*/  pmksa; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitfield_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_group*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wpa_group*) ; 
 int /*<<< orphan*/  pmksa_cache_auth_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_ft_deinit (struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_ft_pmk_cache_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_rekey_gmk ; 
 int /*<<< orphan*/  wpa_rekey_gtk ; 

void wpa_deinit(struct wpa_authenticator *wpa_auth)
{
	struct wpa_group *group, *prev;

	eloop_cancel_timeout(wpa_rekey_gmk, wpa_auth, NULL);
	eloop_cancel_timeout(wpa_rekey_gtk, wpa_auth, NULL);

	pmksa_cache_auth_deinit(wpa_auth->pmksa);

#ifdef CONFIG_IEEE80211R_AP
	wpa_ft_pmk_cache_deinit(wpa_auth->ft_pmk_cache);
	wpa_auth->ft_pmk_cache = NULL;
	wpa_ft_deinit(wpa_auth);
#endif /* CONFIG_IEEE80211R_AP */

#ifdef CONFIG_P2P
	bitfield_free(wpa_auth->ip_pool);
#endif /* CONFIG_P2P */


	os_free(wpa_auth->wpa_ie);

	group = wpa_auth->group;
	while (group) {
		prev = group;
		group = group->next;
		os_free(prev);
	}

	os_free(wpa_auth);
}