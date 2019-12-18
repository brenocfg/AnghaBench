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
typedef  int u32 ;

/* Variables and functions */
 int WLAN_STA_ASSOC ; 
 int WLAN_STA_AUTH ; 
 int WLAN_STA_AUTHORIZED ; 
 int WLAN_STA_GAS ; 
 int WLAN_STA_HT ; 
 int WLAN_STA_MAYBE_WPS ; 
 int WLAN_STA_MFP ; 
 int WLAN_STA_NONERP ; 
 int WLAN_STA_PENDING_POLL ; 
 int WLAN_STA_PREAUTH ; 
 int WLAN_STA_SHORT_PREAMBLE ; 
 int WLAN_STA_VENDOR_VHT ; 
 int WLAN_STA_VHT ; 
 int WLAN_STA_WDS ; 
 int WLAN_STA_WMM ; 
 int WLAN_STA_WNM_SLEEP_MODE ; 
 int WLAN_STA_WPS ; 
 int WLAN_STA_WPS2 ; 
 int os_snprintf (char*,size_t,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 

int ap_sta_flags_txt(u32 flags, char *buf, size_t buflen)
{
	int res;

	buf[0] = '\0';
	res = os_snprintf(buf, buflen, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
			  (flags & WLAN_STA_AUTH ? "[AUTH]" : ""),
			  (flags & WLAN_STA_ASSOC ? "[ASSOC]" : ""),
			  (flags & WLAN_STA_AUTHORIZED ? "[AUTHORIZED]" : ""),
			  (flags & WLAN_STA_PENDING_POLL ? "[PENDING_POLL" :
			   ""),
			  (flags & WLAN_STA_SHORT_PREAMBLE ?
			   "[SHORT_PREAMBLE]" : ""),
			  (flags & WLAN_STA_PREAUTH ? "[PREAUTH]" : ""),
			  (flags & WLAN_STA_WMM ? "[WMM]" : ""),
			  (flags & WLAN_STA_MFP ? "[MFP]" : ""),
			  (flags & WLAN_STA_WPS ? "[WPS]" : ""),
			  (flags & WLAN_STA_MAYBE_WPS ? "[MAYBE_WPS]" : ""),
			  (flags & WLAN_STA_WDS ? "[WDS]" : ""),
			  (flags & WLAN_STA_NONERP ? "[NonERP]" : ""),
			  (flags & WLAN_STA_WPS2 ? "[WPS2]" : ""),
			  (flags & WLAN_STA_GAS ? "[GAS]" : ""),
			  (flags & WLAN_STA_HT ? "[HT]" : ""),
			  (flags & WLAN_STA_VHT ? "[VHT]" : ""),
			  (flags & WLAN_STA_VENDOR_VHT ? "[VENDOR_VHT]" : ""),
			  (flags & WLAN_STA_WNM_SLEEP_MODE ?
			   "[WNM_SLEEP_MODE]" : ""));
	if (os_snprintf_error(buflen, res))
		res = -1;

	return res;
}