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
typedef  int uint32_t ;

/* Variables and functions */
 int IEEE80211_IOC_SCAN_ACTIVE ; 
 int IEEE80211_IOC_SCAN_BGSCAN ; 
 int IEEE80211_IOC_SCAN_CHECK ; 
 int IEEE80211_IOC_SCAN_FLUSH ; 
 int IEEE80211_IOC_SCAN_NOBCAST ; 
 int IEEE80211_IOC_SCAN_NOJOIN ; 
 int IEEE80211_IOC_SCAN_NOPICK ; 
 int IEEE80211_IOC_SCAN_ONCE ; 
 int IEEE80211_IOC_SCAN_PICK1ST ; 
 int WlanScanFlagsType_activeScan ; 
 int WlanScanFlagsType_backgroundScan ; 
 int WlanScanFlagsType_chechCashe ; 
 int WlanScanFlagsType_flushCashe ; 
 int WlanScanFlagsType_noAutoSequencing ; 
 int WlanScanFlagsType_noBroadcast ; 
 int WlanScanFlagsType_noSelection ; 
 int WlanScanFlagsType_once ; 
 int WlanScanFlagsType_pickFirst ; 

__attribute__((used)) static uint32_t
wlan_snmp_to_scan_flags(int flags)
{
	int sr_flags = 0;

	if ((flags & (0x1 << WlanScanFlagsType_noSelection)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_NOPICK;
	if ((flags & (0x1 << WlanScanFlagsType_activeScan)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_ACTIVE;
	if ((flags & (0x1 << WlanScanFlagsType_pickFirst)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_PICK1ST;
	if ((flags & (0x1 << WlanScanFlagsType_backgroundScan)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_BGSCAN;
	if ((flags & (0x1 << WlanScanFlagsType_once)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_ONCE;
	if ((flags & (0x1 << WlanScanFlagsType_noBroadcast)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_NOBCAST;
	if ((flags & (0x1 << WlanScanFlagsType_noAutoSequencing)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_NOJOIN;
	if ((flags & (0x1 << WlanScanFlagsType_flushCashe)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_FLUSH;
	if ((flags & (0x1 << WlanScanFlagsType_chechCashe)) != 0)
		sr_flags |= IEEE80211_IOC_SCAN_CHECK;

	return (sr_flags);
}