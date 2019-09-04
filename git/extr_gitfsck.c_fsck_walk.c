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
struct tree {int dummy; } ;
struct tag {int dummy; } ;
struct object {int type; int /*<<< orphan*/  oid; } ;
struct fsck_options {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
#define  OBJ_BLOB 131 
#define  OBJ_COMMIT 130 
 int OBJ_NONE ; 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  describe_object (struct fsck_options*,struct object*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int fsck_walk_commit (struct commit*,void*,struct fsck_options*) ; 
 int fsck_walk_tag (struct tag*,void*,struct fsck_options*) ; 
 int fsck_walk_tree (struct tree*,void*,struct fsck_options*) ; 
 int /*<<< orphan*/  parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

int fsck_walk(struct object *obj, void *data, struct fsck_options *options)
{
	if (!obj)
		return -1;

	if (obj->type == OBJ_NONE)
		parse_object(the_repository, &obj->oid);

	switch (obj->type) {
	case OBJ_BLOB:
		return 0;
	case OBJ_TREE:
		return fsck_walk_tree((struct tree *)obj, data, options);
	case OBJ_COMMIT:
		return fsck_walk_commit((struct commit *)obj, data, options);
	case OBJ_TAG:
		return fsck_walk_tag((struct tag *)obj, data, options);
	default:
		error("Unknown object type for %s", describe_object(options, obj));
		return -1;
	}
}