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
struct wpa_authenticator {scalar_t__ pmksa; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmksa_cache_auth_flush (scalar_t__) ; 

void wpa_auth_pmksa_flush(struct wpa_authenticator *wpa_auth)
{
	if (wpa_auth && wpa_auth->pmksa)
		pmksa_cache_auth_flush(wpa_auth->pmksa);
}