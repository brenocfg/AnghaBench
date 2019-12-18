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
 int IEEE80211_CHAN_A ; 
 int IEEE80211_CHAN_B ; 
 int IEEE80211_CHAN_FHSS ; 
 int IEEE80211_CHAN_G ; 
#define  NDIS_80211_NETTYPE_11DS 131 
#define  NDIS_80211_NETTYPE_11FH 130 
#define  NDIS_80211_NETTYPE_11OFDM24 129 
#define  NDIS_80211_NETTYPE_11OFDM5 128 

__attribute__((used)) static int
ndis_nettype_chan(uint32_t type)
{
	switch (type) {
	case NDIS_80211_NETTYPE_11FH:		return (IEEE80211_CHAN_FHSS);
	case NDIS_80211_NETTYPE_11DS:		return (IEEE80211_CHAN_B);
	case NDIS_80211_NETTYPE_11OFDM5:	return (IEEE80211_CHAN_A);
	case NDIS_80211_NETTYPE_11OFDM24:	return (IEEE80211_CHAN_G);
	}
	DPRINTF(("unknown channel nettype %d\n", type));
	return (IEEE80211_CHAN_B);	/* Default to 11B chan */
}