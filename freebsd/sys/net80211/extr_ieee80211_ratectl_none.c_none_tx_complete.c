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
struct ieee80211_ratectl_tx_status {int dummy; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
none_tx_complete(const struct ieee80211_node *ni,
    const struct ieee80211_ratectl_tx_status *status)
{
}