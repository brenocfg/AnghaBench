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
struct mwl_frame_bar {int dummy; } ;
struct ieee80211_frame_min {int dummy; } ;
struct ieee80211_frame_ack {int dummy; } ;
struct ieee80211_frame {int* i_fc; } ;

/* Variables and functions */
#define  IEEE80211_FC0_SUBTYPE_ACK 130 
#define  IEEE80211_FC0_SUBTYPE_BAR 129 
#define  IEEE80211_FC0_SUBTYPE_CTS 128 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 int ieee80211_hdrsize (void const*) ; 

__attribute__((used)) static __inline int
mwl_anyhdrsize(const void *data)
{
	const struct ieee80211_frame *wh = data;

	if ((wh->i_fc[0]&IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_CTL) {
		switch (wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) {
		case IEEE80211_FC0_SUBTYPE_CTS:
		case IEEE80211_FC0_SUBTYPE_ACK:
			return sizeof(struct ieee80211_frame_ack);
		case IEEE80211_FC0_SUBTYPE_BAR:
			return sizeof(struct mwl_frame_bar);
		}
		return sizeof(struct ieee80211_frame_min);
	} else
		return ieee80211_hdrsize(data);
}