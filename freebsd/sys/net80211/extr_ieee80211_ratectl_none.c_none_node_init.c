#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* rs_rates; } ;
struct ieee80211_node {int ni_txrate; TYPE_1__ ni_rates; } ;

/* Variables and functions */
 int IEEE80211_RATE_VAL ; 

__attribute__((used)) static void
none_node_init(struct ieee80211_node *ni)
{
	ni->ni_txrate = ni->ni_rates.rs_rates[0] & IEEE80211_RATE_VAL;
}