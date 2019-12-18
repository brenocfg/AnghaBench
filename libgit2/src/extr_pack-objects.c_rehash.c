#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_pobject ;
struct TYPE_6__ {size_t nr_objects; int /*<<< orphan*/  object_ix; TYPE_1__* object_list; } ;
typedef  TYPE_2__ git_packbuilder ;

/* Variables and functions */
 int /*<<< orphan*/  git_oidmap_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ git_oidmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int rehash(git_packbuilder *pb)
{
	git_pobject *po;
	size_t i;

	git_oidmap_clear(pb->object_ix);

	for (i = 0, po = pb->object_list; i < pb->nr_objects; i++, po++) {
		if (git_oidmap_set(pb->object_ix, &po->id, po) < 0)
			return -1;
	}

	return 0;
}