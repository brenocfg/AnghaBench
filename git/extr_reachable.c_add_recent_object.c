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
typedef  scalar_t__ timestamp_t ;
struct recent_data {scalar_t__ timestamp; int /*<<< orphan*/  revs; } ;
struct object_id {int dummy; } ;
struct object {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
#define  OBJ_BLOB 131 
#define  OBJ_COMMIT 130 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  add_pending_object (int /*<<< orphan*/ ,struct object*,char*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ lookup_blob (int /*<<< orphan*/ ,struct object_id const*) ; 
 scalar_t__ lookup_tree (int /*<<< orphan*/ ,struct object_id const*) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct object* parse_object_or_die (struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  type_name (int) ; 

__attribute__((used)) static void add_recent_object(const struct object_id *oid,
			      timestamp_t mtime,
			      struct recent_data *data)
{
	struct object *obj;
	enum object_type type;

	if (mtime <= data->timestamp)
		return;

	/*
	 * We do not want to call parse_object here, because
	 * inflating blobs and trees could be very expensive.
	 * However, we do need to know the correct type for
	 * later processing, and the revision machinery expects
	 * commits and tags to have been parsed.
	 */
	type = oid_object_info(the_repository, oid, NULL);
	if (type < 0)
		die("unable to get object info for %s", oid_to_hex(oid));

	switch (type) {
	case OBJ_TAG:
	case OBJ_COMMIT:
		obj = parse_object_or_die(oid, NULL);
		break;
	case OBJ_TREE:
		obj = (struct object *)lookup_tree(the_repository, oid);
		break;
	case OBJ_BLOB:
		obj = (struct object *)lookup_blob(the_repository, oid);
		break;
	default:
		die("unknown object type for %s: %s",
		    oid_to_hex(oid), type_name(type));
	}

	if (!obj)
		die("unable to lookup %s", oid_to_hex(oid));

	add_pending_object(data->revs, obj, "");
}