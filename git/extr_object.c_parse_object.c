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
struct object {scalar_t__ type; scalar_t__ parsed; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 scalar_t__ OBJ_BLOB ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_object_signature (struct object_id const*,void*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  lookup_blob (struct repository*,struct object_id const*) ; 
 struct object* lookup_object (struct repository*,struct object_id const*) ; 
 struct object_id* lookup_replace_object (struct repository*,struct object_id const*) ; 
 scalar_t__ oid_object_info (struct repository*,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  parse_blob_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct object* parse_object_buffer (struct repository*,struct object_id const*,int,unsigned long,void*,int*) ; 
 scalar_t__ repo_has_object_file (struct repository*,struct object_id const*) ; 
 void* repo_read_object_file (struct repository*,struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/ * type_name (int) ; 

struct object *parse_object(struct repository *r, const struct object_id *oid)
{
	unsigned long size;
	enum object_type type;
	int eaten;
	const struct object_id *repl = lookup_replace_object(r, oid);
	void *buffer;
	struct object *obj;

	obj = lookup_object(r, oid);
	if (obj && obj->parsed)
		return obj;

	if ((obj && obj->type == OBJ_BLOB && repo_has_object_file(r, oid)) ||
	    (!obj && repo_has_object_file(r, oid) &&
	     oid_object_info(r, oid, NULL) == OBJ_BLOB)) {
		if (check_object_signature(repl, NULL, 0, NULL) < 0) {
			error(_("hash mismatch %s"), oid_to_hex(oid));
			return NULL;
		}
		parse_blob_buffer(lookup_blob(r, oid), NULL, 0);
		return lookup_object(r, oid);
	}

	buffer = repo_read_object_file(r, oid, &type, &size);
	if (buffer) {
		if (check_object_signature(repl, buffer, size, type_name(type)) < 0) {
			free(buffer);
			error(_("hash mismatch %s"), oid_to_hex(repl));
			return NULL;
		}

		obj = parse_object_buffer(r, oid, type, size,
					  buffer, &eaten);
		if (!eaten)
			free(buffer);
		return obj;
	}
	return NULL;
}