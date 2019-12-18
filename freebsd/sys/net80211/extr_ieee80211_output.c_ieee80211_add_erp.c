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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {scalar_t__ ic_nonerpsta; int ic_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ELEMID_ERP ; 
 int /*<<< orphan*/  IEEE80211_ERP_LONG_PREAMBLE ; 
 int /*<<< orphan*/  IEEE80211_ERP_NON_ERP_PRESENT ; 
 int /*<<< orphan*/  IEEE80211_ERP_USE_PROTECTION ; 
 int IEEE80211_F_USEBARKER ; 
 int IEEE80211_F_USEPROT ; 

__attribute__((used)) static uint8_t *
ieee80211_add_erp(uint8_t *frm, struct ieee80211com *ic)
{
	uint8_t erp;

	*frm++ = IEEE80211_ELEMID_ERP;
	*frm++ = 1;
	erp = 0;
	if (ic->ic_nonerpsta != 0)
		erp |= IEEE80211_ERP_NON_ERP_PRESENT;
	if (ic->ic_flags & IEEE80211_F_USEPROT)
		erp |= IEEE80211_ERP_USE_PROTECTION;
	if (ic->ic_flags & IEEE80211_F_USEBARKER)
		erp |= IEEE80211_ERP_LONG_PREAMBLE;
	*frm++ = erp;
	return frm;
}