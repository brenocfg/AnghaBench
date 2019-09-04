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
struct object {int type; } ;
struct atom_value {int dummy; } ;

/* Variables and functions */
#define  OBJ_BLOB 131 
#define  OBJ_COMMIT 130 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  grab_commit_values (struct atom_value*,int,struct object*) ; 
 int /*<<< orphan*/  grab_person (char*,struct atom_value*,int,void*) ; 
 int /*<<< orphan*/  grab_sub_body_contents (struct atom_value*,int,void*) ; 
 int /*<<< orphan*/  grab_tag_values (struct atom_value*,int,struct object*) ; 

__attribute__((used)) static void grab_values(struct atom_value *val, int deref, struct object *obj, void *buf)
{
	switch (obj->type) {
	case OBJ_TAG:
		grab_tag_values(val, deref, obj);
		grab_sub_body_contents(val, deref, buf);
		grab_person("tagger", val, deref, buf);
		break;
	case OBJ_COMMIT:
		grab_commit_values(val, deref, obj);
		grab_sub_body_contents(val, deref, buf);
		grab_person("author", val, deref, buf);
		grab_person("committer", val, deref, buf);
		break;
	case OBJ_TREE:
		/* grab_tree_values(val, deref, obj, buf, sz); */
		break;
	case OBJ_BLOB:
		/* grab_blob_values(val, deref, obj, buf, sz); */
		break;
	default:
		die("Eh?  Object of type %d?", obj->type);
	}
}