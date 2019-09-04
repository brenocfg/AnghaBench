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
struct object {int /*<<< orphan*/  oid; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  MA_ALLOW_ANY 131 
#define  MA_ALLOW_PROMISOR 130 
#define  MA_ERROR 129 
#define  MA_PRINT 128 
 int arg_missing_action ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_promisor_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  missing_objects ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidset_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void finish_object__ma(struct object *obj)
{
	/*
	 * Whether or not we try to dynamically fetch missing objects
	 * from the server, we currently DO NOT have the object.  We
	 * can either print, allow (ignore), or conditionally allow
	 * (ignore) them.
	 */
	switch (arg_missing_action) {
	case MA_ERROR:
		die("missing %s object '%s'",
		    type_name(obj->type), oid_to_hex(&obj->oid));
		return;

	case MA_ALLOW_ANY:
		return;

	case MA_PRINT:
		oidset_insert(&missing_objects, &obj->oid);
		return;

	case MA_ALLOW_PROMISOR:
		if (is_promisor_object(&obj->oid))
			return;
		die("unexpected missing %s object '%s'",
		    type_name(obj->type), oid_to_hex(&obj->oid));
		return;

	default:
		BUG("unhandled missing_action");
		return;
	}
}