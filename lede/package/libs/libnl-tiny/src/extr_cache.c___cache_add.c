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
struct nl_object {int /*<<< orphan*/  ce_list; struct nl_cache* ce_cache; } ;
struct nl_cache {int /*<<< orphan*/  c_nitems; int /*<<< orphan*/  c_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_object*,struct nl_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_cache_name (struct nl_cache*) ; 
 int /*<<< orphan*/  nl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __cache_add(struct nl_cache *cache, struct nl_object *obj)
{
	obj->ce_cache = cache;

	nl_list_add_tail(&obj->ce_list, &cache->c_items);
	cache->c_nitems++;

	NL_DBG(1, "Added %p to cache %p <%s>.\n",
	       obj, cache, nl_cache_name(cache));

	return 0;
}