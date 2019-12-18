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
struct ieee80211_node {int /*<<< orphan*/  ni_noise; } ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  node_getrssi (struct ieee80211_node const*) ; 

__attribute__((used)) static void
node_getsignal(const struct ieee80211_node *ni, int8_t *rssi, int8_t *noise)
{
	*rssi = node_getrssi(ni);
	*noise = ni->ni_noise;
}