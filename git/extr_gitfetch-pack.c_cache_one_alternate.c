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
struct object_id {int dummy; } ;
struct object {int flags; } ;
struct alternate_object_cache {scalar_t__ nr; struct object** items; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct object**,scalar_t__,int /*<<< orphan*/ ) ; 
 int ALTERNATE ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void cache_one_alternate(const struct object_id *oid,
				void *vcache)
{
	struct alternate_object_cache *cache = vcache;
	struct object *obj = parse_object(the_repository, oid);

	if (!obj || (obj->flags & ALTERNATE))
		return;

	obj->flags |= ALTERNATE;
	ALLOC_GROW(cache->items, cache->nr + 1, cache->alloc);
	cache->items[cache->nr++] = obj;
}