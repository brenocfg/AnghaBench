#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct merge_list {int stage; struct merge_list* link; TYPE_2__* blob; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 void* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 

__attribute__((used)) static void *origin(struct merge_list *entry, unsigned long *size)
{
	enum object_type type;
	while (entry) {
		if (entry->stage == 2)
			return read_object_file(&entry->blob->object.oid,
						&type, size);
		entry = entry->link;
	}
	return NULL;
}