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
struct object_id {int dummy; } ;
struct object {int flags; scalar_t__ type; int /*<<< orphan*/  oid; } ;
struct fsck_options {int /*<<< orphan*/  walk; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 struct fsck_options FSCK_OPTIONS_DEFAULT ; 
 int HAS_OBJ ; 
 scalar_t__ OBJ_NONE ; 
 int REACHABLE ; 
 int /*<<< orphan*/  fsck_walk (struct object*,int /*<<< orphan*/ *,struct fsck_options*) ; 
 struct object* lookup_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  mark_used ; 
 int /*<<< orphan*/  object_as_type (int /*<<< orphan*/ ,struct object*,int,int /*<<< orphan*/ ) ; 
 int oid_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void mark_unreachable_referents(const struct object_id *oid)
{
	struct fsck_options options = FSCK_OPTIONS_DEFAULT;
	struct object *obj = lookup_object(the_repository, oid);

	if (!obj || !(obj->flags & HAS_OBJ))
		return; /* not part of our original set */
	if (obj->flags & REACHABLE)
		return; /* reachable objects already traversed */

	/*
	 * Avoid passing OBJ_NONE to fsck_walk, which will parse the object
	 * (and we want to avoid parsing blobs).
	 */
	if (obj->type == OBJ_NONE) {
		enum object_type type = oid_object_info(the_repository,
							&obj->oid, NULL);
		if (type > 0)
			object_as_type(the_repository, obj, type, 0);
	}

	options.walk = mark_used;
	fsck_walk(obj, NULL, &options);
}