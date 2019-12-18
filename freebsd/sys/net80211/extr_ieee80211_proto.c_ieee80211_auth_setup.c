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

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AUTH_AUTO ; 
 int /*<<< orphan*/  IEEE80211_AUTH_OPEN ; 
 int /*<<< orphan*/  IEEE80211_AUTH_SHARED ; 
 int /*<<< orphan*/  auth_internal ; 
 int /*<<< orphan*/  ieee80211_authenticator_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ieee80211_auth_setup(void)
{
	ieee80211_authenticator_register(IEEE80211_AUTH_OPEN, &auth_internal);
	ieee80211_authenticator_register(IEEE80211_AUTH_SHARED, &auth_internal);
	ieee80211_authenticator_register(IEEE80211_AUTH_AUTO, &auth_internal);
}