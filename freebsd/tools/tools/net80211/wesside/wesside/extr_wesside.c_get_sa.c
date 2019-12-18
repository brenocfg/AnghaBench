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
struct ieee80211_frame {int* i_fc; void* i_addr3; void* i_addr2; } ;

/* Variables and functions */
 int IEEE80211_FC1_DIR_FROMDS ; 

void *get_sa(struct ieee80211_frame *wh)
{       
        if (wh->i_fc[1] & IEEE80211_FC1_DIR_FROMDS)
                return wh->i_addr3;
        else    
                return wh->i_addr2;
}