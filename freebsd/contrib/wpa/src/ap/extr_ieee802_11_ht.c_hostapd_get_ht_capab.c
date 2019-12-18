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
typedef  int u16 ;
struct ieee80211_ht_capabilities {int /*<<< orphan*/  ht_capabilities_info; } ;
struct hostapd_data {TYPE_1__* iconf; } ;
struct TYPE_2__ {int ht_capab; } ;

/* Variables and functions */
 int HT_CAP_INFO_RX_STBC_MASK ; 
 int HT_CAP_INFO_SMPS_MASK ; 
 int HT_CAP_INFO_TX_STBC ; 
 int /*<<< orphan*/  host_to_le16 (int) ; 
 int le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (struct ieee80211_ht_capabilities*,struct ieee80211_ht_capabilities*,int) ; 

void hostapd_get_ht_capab(struct hostapd_data *hapd,
			  struct ieee80211_ht_capabilities *ht_cap,
			  struct ieee80211_ht_capabilities *neg_ht_cap)
{
	u16 cap;

	if (ht_cap == NULL)
		return;
	os_memcpy(neg_ht_cap, ht_cap, sizeof(*neg_ht_cap));
	cap = le_to_host16(neg_ht_cap->ht_capabilities_info);

	/*
	 * Mask out HT features we don't support, but don't overwrite
	 * non-symmetric features like STBC and SMPS. Just because
	 * we're not in dynamic SMPS mode the STA might still be.
	 */
	cap &= (hapd->iconf->ht_capab | HT_CAP_INFO_RX_STBC_MASK |
		HT_CAP_INFO_TX_STBC | HT_CAP_INFO_SMPS_MASK);

	/*
	 * STBC needs to be handled specially
	 * if we don't support RX STBC, mask out TX STBC in the STA's HT caps
	 * if we don't support TX STBC, mask out RX STBC in the STA's HT caps
	 */
	if (!(hapd->iconf->ht_capab & HT_CAP_INFO_RX_STBC_MASK))
		cap &= ~HT_CAP_INFO_TX_STBC;
	if (!(hapd->iconf->ht_capab & HT_CAP_INFO_TX_STBC))
		cap &= ~HT_CAP_INFO_RX_STBC_MASK;

	neg_ht_cap->ht_capabilities_info = host_to_le16(cap);
}