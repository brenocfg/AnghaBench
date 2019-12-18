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
struct cache {struct cache* next_local; } ;

/* Variables and functions */

__attribute__((used)) static void link_cache_lists(struct cache *smaller, struct cache *bigger)
{
	while (smaller->next_local) {
		if (smaller->next_local == bigger)
			return; /* already linked */
		smaller = smaller->next_local;
	}

	smaller->next_local = bigger;
}