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
struct pt_tnt_cache {unsigned long long tnt; unsigned long long index; } ;

/* Variables and functions */

void pt_tnt_cache_init(struct pt_tnt_cache *cache)
{
	if (!cache)
		return;

	cache->tnt = 0ull;
	cache->index = 0ull;
}