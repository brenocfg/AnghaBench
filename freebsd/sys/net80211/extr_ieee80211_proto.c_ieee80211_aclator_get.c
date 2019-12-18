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
struct ieee80211_aclator {int /*<<< orphan*/  iac_name; } ;

/* Variables and functions */
 struct ieee80211_aclator const* acl ; 
 int /*<<< orphan*/  ieee80211_load_module (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

const struct ieee80211_aclator *
ieee80211_aclator_get(const char *name)
{
	if (acl == NULL)
		ieee80211_load_module("wlan_acl");
	return acl != NULL && strcmp(acl->iac_name, name) == 0 ? acl : NULL;
}