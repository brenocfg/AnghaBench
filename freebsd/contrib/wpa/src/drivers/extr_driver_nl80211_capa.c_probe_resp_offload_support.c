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
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_80211U ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 ; 
 unsigned int WPA_DRIVER_PROBE_RESP_OFFLOAD_INTERWORKING ; 
 unsigned int WPA_DRIVER_PROBE_RESP_OFFLOAD_P2P ; 
 unsigned int WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS ; 
 unsigned int WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS2 ; 

__attribute__((used)) static unsigned int probe_resp_offload_support(int supp_protocols)
{
	unsigned int prot = 0;

	if (supp_protocols & NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS)
		prot |= WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS;
	if (supp_protocols & NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2)
		prot |= WPA_DRIVER_PROBE_RESP_OFFLOAD_WPS2;
	if (supp_protocols & NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P)
		prot |= WPA_DRIVER_PROBE_RESP_OFFLOAD_P2P;
	if (supp_protocols & NL80211_PROBE_RESP_OFFLOAD_SUPPORT_80211U)
		prot |= WPA_DRIVER_PROBE_RESP_OFFLOAD_INTERWORKING;

	return prot;
}