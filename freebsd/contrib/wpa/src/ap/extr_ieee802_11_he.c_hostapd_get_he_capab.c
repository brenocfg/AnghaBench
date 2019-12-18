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
struct ieee80211_he_capabilities {int dummy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memcpy (struct ieee80211_he_capabilities*,struct ieee80211_he_capabilities const*,size_t) ; 

void hostapd_get_he_capab(struct hostapd_data *hapd,
			  const struct ieee80211_he_capabilities *he_cap,
			  struct ieee80211_he_capabilities *neg_he_cap,
			  size_t he_capab_len)
{
	if (!he_cap)
		return;

	if (he_capab_len > sizeof(*neg_he_cap))
		he_capab_len = sizeof(*neg_he_cap);
	/* TODO: mask out unsupported features */

	os_memcpy(neg_he_cap, he_cap, he_capab_len);
}