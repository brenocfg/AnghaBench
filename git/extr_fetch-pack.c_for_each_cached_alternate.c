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
struct fetch_negotiator {int dummy; } ;
struct alternate_object_cache {size_t nr; struct object** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_one_alternate ; 
 int /*<<< orphan*/  for_each_alternate_ref (int /*<<< orphan*/ ,struct alternate_object_cache*) ; 

__attribute__((used)) static void for_each_cached_alternate(struct fetch_negotiator *negotiator,
				      void (*cb)(struct fetch_negotiator *,
						 struct object *))
{
	static int initialized;
	static struct alternate_object_cache cache;
	size_t i;

	if (!initialized) {
		for_each_alternate_ref(cache_one_alternate, &cache);
		initialized = 1;
	}

	for (i = 0; i < cache.nr; i++)
		cb(negotiator, cache.items[i]);
}