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
struct object_id {int dummy; } ;
struct commit_list {TYPE_2__* item; struct commit_list* next; } ;
struct commit {struct commit_list* parents; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ oideq (int /*<<< orphan*/ *,struct object_id const*) ; 

__attribute__((used)) static int which_parent(const struct object_id *oid, const struct commit *commit)
{
	int nth;
	const struct commit_list *parent;

	for (nth = 0, parent = commit->parents; parent; parent = parent->next) {
		if (oideq(&parent->item->object.oid, oid))
			return nth;
		nth++;
	}
	return -1;
}