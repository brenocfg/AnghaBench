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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211_channel {int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */

uint32_t
ieee80211_get_channel_center_freq(const struct ieee80211_channel *c)
{

	return (c->ic_freq);
}