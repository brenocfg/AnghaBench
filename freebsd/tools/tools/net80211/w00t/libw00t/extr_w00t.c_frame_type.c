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
struct ieee80211_frame {int* i_fc; } ;

/* Variables and functions */
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_TYPE_MASK ; 

int frame_type(struct ieee80211_frame *wh, int type, int stype)
{       
        if ((wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) != type)
                return 0;

        if ((wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) != stype)
                return 0;

        return 1;
}