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
struct object {scalar_t__ type; } ;
struct handle_one_ref_cb {int /*<<< orphan*/  repo; struct commit_list** list; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 struct object* deref_tag (int /*<<< orphan*/ ,struct object*,char const*,int /*<<< orphan*/ ) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int handle_one_ref(const char *path, const struct object_id *oid,
			  int flag, void *cb_data)
{
	struct handle_one_ref_cb *cb = cb_data;
	struct commit_list **list = cb->list;
	struct object *object = parse_object(cb->repo, oid);
	if (!object)
		return 0;
	if (object->type == OBJ_TAG) {
		object = deref_tag(cb->repo, object, path,
				   strlen(path));
		if (!object)
			return 0;
	}
	if (object->type != OBJ_COMMIT)
		return 0;
	commit_list_insert((struct commit *)object, list);
	return 0;
}