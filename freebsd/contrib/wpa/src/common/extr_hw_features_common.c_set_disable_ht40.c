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
struct ieee80211_ht_capabilities {int /*<<< orphan*/  ht_capabilities_info; } ;
typedef  int /*<<< orphan*/  le16 ;

/* Variables and functions */
 int HT_CAP_INFO_SHORT_GI40MHZ ; 
 int HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET ; 
 int /*<<< orphan*/  host_to_le16 (int) ; 

void set_disable_ht40(struct ieee80211_ht_capabilities *htcaps,
		      int disabled)
{
	/* Masking these out disables HT40 */
	le16 msk = host_to_le16(HT_CAP_INFO_SUPP_CHANNEL_WIDTH_SET |
				HT_CAP_INFO_SHORT_GI40MHZ);

	if (disabled)
		htcaps->ht_capabilities_info &= ~msk;
	else
		htcaps->ht_capabilities_info |= msk;
}