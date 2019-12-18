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
struct object {int flags; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_REACHABLE ; 
 int HAS_OBJ ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  describe_object (struct object*) ; 
 int /*<<< orphan*/  errors_found ; 
 scalar_t__ has_object_pack (int /*<<< orphan*/ *) ; 
 scalar_t__ is_promisor_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printable_type (struct object*) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_reachable_object(struct object *obj)
{
	/*
	 * We obviously want the object to be parsed,
	 * except if it was in a pack-file and we didn't
	 * do a full fsck
	 */
	if (!(obj->flags & HAS_OBJ)) {
		if (is_promisor_object(&obj->oid))
			return;
		if (has_object_pack(&obj->oid))
			return; /* it is in pack - forget about it */
		printf_ln(_("missing %s %s"), printable_type(obj),
			  describe_object(obj));
		errors_found |= ERROR_REACHABLE;
		return;
	}
}