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
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int IEEE80211_MODE_11A ; 
 int IEEE80211_MODE_11B ; 
 int IEEE80211_MODE_11G ; 
 int IEEE80211_MODE_AUTO ; 
 int IEEE80211_MODE_FH ; 
#define  NDIS_80211_NETTYPE_11DS 131 
#define  NDIS_80211_NETTYPE_11FH 130 
#define  NDIS_80211_NETTYPE_11OFDM24 129 
#define  NDIS_80211_NETTYPE_11OFDM5 128 

__attribute__((used)) static int
ndis_nettype_mode(uint32_t type)
{
	switch (type) {
	case NDIS_80211_NETTYPE_11FH:		return (IEEE80211_MODE_FH);
	case NDIS_80211_NETTYPE_11DS:		return (IEEE80211_MODE_11B);
	case NDIS_80211_NETTYPE_11OFDM5:	return (IEEE80211_MODE_11A);
	case NDIS_80211_NETTYPE_11OFDM24:	return (IEEE80211_MODE_11G);
	}
	DPRINTF(("unknown mode nettype %d\n", type));
	return (IEEE80211_MODE_AUTO);
}