#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_3__* objects; } ;
struct object_id {int dummy; } ;
struct TYPE_6__ {TYPE_2__* replace_map; } ;
struct TYPE_4__ {scalar_t__ tablesize; } ;
struct TYPE_5__ {TYPE_1__ map; } ;

/* Variables and functions */
 struct object_id const* do_lookup_replace_object (struct repository*,struct object_id const*) ; 
 int /*<<< orphan*/  read_replace_refs ; 

__attribute__((used)) static inline const struct object_id *lookup_replace_object(struct repository *r,
							    const struct object_id *oid)
{
	if (!read_replace_refs ||
	    (r->objects->replace_map &&
	     r->objects->replace_map->map.tablesize == 0))
		return oid;
	return do_lookup_replace_object(r, oid);
}