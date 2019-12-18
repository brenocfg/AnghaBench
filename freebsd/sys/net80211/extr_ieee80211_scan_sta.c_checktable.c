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
struct scanlist {scalar_t__* list; int count; } ;
struct ieee80211_channel {scalar_t__ ic_freq; } ;

/* Variables and functions */

__attribute__((used)) static int
checktable(const struct scanlist *scan, const struct ieee80211_channel *c)
{
	int i;

	for (; scan->list != NULL; scan++) {
		for (i = 0; i < scan->count; i++)
			if (scan->list[i] == c->ic_freq) 
				return 1;
	}
	return 0;
}