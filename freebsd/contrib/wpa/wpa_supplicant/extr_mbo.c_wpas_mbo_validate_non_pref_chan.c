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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ MBO_NON_PREF_CHAN_REASON_INT_INTERFERENCE ; 
 int ieee80211_chan_to_freq (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int wpas_mbo_validate_non_pref_chan(u8 oper_class, u8 chan, u8 reason)
{
	if (reason > MBO_NON_PREF_CHAN_REASON_INT_INTERFERENCE)
		return -1;

	/* Only checking the validity of the channel and oper_class */
	if (ieee80211_chan_to_freq(NULL, oper_class, chan) == -1)
		return -1;

	return 0;
}