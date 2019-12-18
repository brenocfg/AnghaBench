#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct walker {int /*<<< orphan*/  (* prefetch ) (struct walker*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  hash; } ;
struct object {int flags; TYPE_3__ oid; } ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int COMPLETE ; 
 int SEEN ; 
 int TO_SCAN ; 
 scalar_t__ has_object_file (TYPE_3__*) ; 
 int /*<<< orphan*/  object_list_insert (struct object*,TYPE_1__**) ; 
 TYPE_1__** process_queue_end ; 
 int /*<<< orphan*/  stub1 (struct walker*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process(struct walker *walker, struct object *obj)
{
	if (obj->flags & SEEN)
		return 0;
	obj->flags |= SEEN;

	if (has_object_file(&obj->oid)) {
		/* We already have it, so we should scan it now. */
		obj->flags |= TO_SCAN;
	}
	else {
		if (obj->flags & COMPLETE)
			return 0;
		walker->prefetch(walker, obj->oid.hash);
	}

	object_list_insert(obj, process_queue_end);
	process_queue_end = &(*process_queue_end)->next;
	return 0;
}