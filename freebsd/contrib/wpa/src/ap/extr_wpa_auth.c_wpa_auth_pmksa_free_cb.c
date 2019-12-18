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
struct wpa_authenticator {int dummy; } ;
struct rsn_pmksa_cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_auth_for_each_sta (struct wpa_authenticator*,int /*<<< orphan*/ ,struct rsn_pmksa_cache_entry*) ; 
 int /*<<< orphan*/  wpa_auth_pmksa_clear_cb ; 

__attribute__((used)) static void wpa_auth_pmksa_free_cb(struct rsn_pmksa_cache_entry *entry,
				   void *ctx)
{
	struct wpa_authenticator *wpa_auth = ctx;
	wpa_auth_for_each_sta(wpa_auth, wpa_auth_pmksa_clear_cb, entry);
}