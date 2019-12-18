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
struct params {int /*<<< orphan*/  tx; int /*<<< orphan*/  mac; } ;
struct ieee80211_frame {int* i_fc; int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;

/* Variables and functions */
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ack(struct params *p, struct ieee80211_frame *wh)
{       
        if (memcmp(wh->i_addr1, p->mac, 6) != 0)
                return;

        if ((wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_CTL)
                return;

        send_ack(p->tx, wh->i_addr2);
}