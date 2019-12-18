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
struct name_cache {size_t size; TYPE_1__* cache; } ;
struct TYPE_2__ {struct name_cache* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct name_cache*) ; 

__attribute__((used)) static void
free_cache(struct name_cache *cache)
{
	size_t i;

	if (cache != NULL) {
		for (i = 0; i < cache->size; i++)
			free(cache->cache[i].name);
		free(cache);
	}
}