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
struct object {scalar_t__ type; } ;
struct fsck_options {int dummy; } ;
struct commit {int dummy; } ;
struct blob {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCK_MSG_BAD_OBJECT_SHA1 ; 
 int /*<<< orphan*/  FSCK_MSG_UNKNOWN_TYPE ; 
 scalar_t__ OBJ_BLOB ; 
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 scalar_t__ OBJ_TREE ; 
 int fsck_blob (struct blob*,void*,unsigned long,struct fsck_options*) ; 
 int fsck_commit (struct commit*,char const*,unsigned long,struct fsck_options*) ; 
 int fsck_tag (struct tag*,char const*,unsigned long,struct fsck_options*) ; 
 int fsck_tree (struct tree*,struct fsck_options*) ; 
 int report (struct fsck_options*,struct object*,int /*<<< orphan*/ ,char*,...) ; 

int fsck_object(struct object *obj, void *data, unsigned long size,
	struct fsck_options *options)
{
	if (!obj)
		return report(options, obj, FSCK_MSG_BAD_OBJECT_SHA1, "no valid object to fsck");

	if (obj->type == OBJ_BLOB)
		return fsck_blob((struct blob *)obj, data, size, options);
	if (obj->type == OBJ_TREE)
		return fsck_tree((struct tree *) obj, options);
	if (obj->type == OBJ_COMMIT)
		return fsck_commit((struct commit *) obj, (const char *) data,
			size, options);
	if (obj->type == OBJ_TAG)
		return fsck_tag((struct tag *) obj, (const char *) data,
			size, options);

	return report(options, obj, FSCK_MSG_UNKNOWN_TYPE, "unknown type '%d' (internal fsck error)",
			  obj->type);
}