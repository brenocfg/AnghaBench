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
struct nl_object {struct nl_cache* ce_cache; int /*<<< orphan*/  ce_list; } ;
struct nl_cache {int /*<<< orphan*/  c_nitems; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_DBG (int,char*,struct nl_object*,struct nl_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_cache_name (struct nl_cache*) ; 
 int /*<<< orphan*/  nl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl_object_put (struct nl_object*) ; 

void nl_cache_remove(struct nl_object *obj)
{
	struct nl_cache *cache = obj->ce_cache;

	if (cache == NULL)
		return;

	nl_list_del(&obj->ce_list);
	obj->ce_cache = NULL;
	nl_object_put(obj);
	cache->c_nitems--;

	NL_DBG(1, "Deleted %p from cache %p <%s>.\n",
	       obj, cache, nl_cache_name(cache));
}