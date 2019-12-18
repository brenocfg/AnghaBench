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
struct ieee80211_frame {int dummy; } ;
struct arphdr {int dummy; } ;

/* Variables and functions */

int is_arp(struct ieee80211_frame *wh, int len)
{       
        int arpsize = 8 + sizeof(struct arphdr) + 10*2;

        if (len == arpsize || len == 54)
                return 1;

        return 0;
}