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
struct ieee80211_aclator {char* iac_name; } ;

/* Variables and functions */
 struct ieee80211_aclator const* acl ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
ieee80211_aclator_register(const struct ieee80211_aclator *iac)
{
	printf("wlan: %s acl policy registered\n", iac->iac_name);
	acl = iac;
}