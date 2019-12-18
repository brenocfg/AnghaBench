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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ ETH_P_80211_ENCAP ; 
 scalar_t__ ETH_P_EAPOL ; 
 scalar_t__ ETH_P_RSN_PREAUTH ; 

__attribute__((used)) static int wpa_priv_allowed_l2_proto(u16 proto)
{
	return proto == ETH_P_EAPOL || proto == ETH_P_RSN_PREAUTH ||
		proto == ETH_P_80211_ENCAP;
}