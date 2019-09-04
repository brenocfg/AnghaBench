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
struct object {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ MA_ALLOW_PROMISOR ; 
 scalar_t__ arg_missing_action ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  has_object_file (int /*<<< orphan*/ *) ; 
 scalar_t__ is_promisor_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_object (struct object*,char const*,void*) ; 

__attribute__((used)) static void show_object__ma_allow_promisor(struct object *obj, const char *name, void *data)
{
	assert(arg_missing_action == MA_ALLOW_PROMISOR);

	/*
	 * Quietly ignore EXPECTED missing objects.  This avoids problems with
	 * staging them now and getting an odd error later.
	 */
	if (!has_object_file(&obj->oid) && is_promisor_object(&obj->oid))
		return;

	show_object(obj, name, data);
}