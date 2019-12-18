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
struct ieee80211_frame {int /*<<< orphan*/  i_addr1; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

int broadcast(struct ieee80211_frame *wh)
{
	/* XXX multicast */

	if (memcmp(wh->i_addr1, "\xff\xff\xff\xff\xff\xff", 6) == 0)
		return 1;

	return 0;
}