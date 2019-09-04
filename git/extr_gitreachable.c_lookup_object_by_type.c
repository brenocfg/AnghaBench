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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
#define  OBJ_BLOB 131 
#define  OBJ_COMMIT 130 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  die (char*,int) ; 
 void* lookup_blob (struct repository*,struct object_id const*) ; 
 void* lookup_commit (struct repository*,struct object_id const*) ; 
 void* lookup_tag (struct repository*,struct object_id const*) ; 
 void* lookup_tree (struct repository*,struct object_id const*) ; 

__attribute__((used)) static void *lookup_object_by_type(struct repository *r,
				   const struct object_id *oid,
				   enum object_type type)
{
	switch (type) {
	case OBJ_COMMIT:
		return lookup_commit(r, oid);
	case OBJ_TREE:
		return lookup_tree(r, oid);
	case OBJ_TAG:
		return lookup_tag(r, oid);
	case OBJ_BLOB:
		return lookup_blob(r, oid);
	default:
		die("BUG: unknown object type %d", type);
	}
}