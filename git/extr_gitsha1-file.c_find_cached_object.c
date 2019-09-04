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
struct object_id {int dummy; } ;
struct cached_object {struct object_id const oid; } ;
struct TYPE_2__ {struct object_id const* empty_tree; } ;

/* Variables and functions */
 int cached_object_nr ; 
 struct cached_object* cached_objects ; 
 struct cached_object empty_tree ; 
 scalar_t__ oideq (struct object_id const*,struct object_id const*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static struct cached_object *find_cached_object(const struct object_id *oid)
{
	int i;
	struct cached_object *co = cached_objects;

	for (i = 0; i < cached_object_nr; i++, co++) {
		if (oideq(&co->oid, oid))
			return co;
	}
	if (oideq(oid, the_hash_algo->empty_tree))
		return &empty_tree;
	return NULL;
}