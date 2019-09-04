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
struct oidset {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOR_EACH_OBJECT_PROMISOR_ONLY ; 
 int /*<<< orphan*/  add_promisor_object ; 
 int /*<<< orphan*/  for_each_packed_object (int /*<<< orphan*/ ,struct oidset*,int /*<<< orphan*/ ) ; 
 int oidset_contains (struct oidset*,struct object_id const*) ; 
 scalar_t__ repository_format_partial_clone ; 

int is_promisor_object(const struct object_id *oid)
{
	static struct oidset promisor_objects;
	static int promisor_objects_prepared;

	if (!promisor_objects_prepared) {
		if (repository_format_partial_clone) {
			for_each_packed_object(add_promisor_object,
					       &promisor_objects,
					       FOR_EACH_OBJECT_PROMISOR_ONLY);
		}
		promisor_objects_prepared = 1;
	}
	return oidset_contains(&promisor_objects, oid);
}