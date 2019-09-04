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
struct object {int flags; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  ERROR_OBJECT ; 
 int HAS_OBJ ; 
 int OBJ_BLOB ; 
 int REACHABLE ; 
 int SEEN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  errors_found ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fsck_obj (struct object*,void*,unsigned long) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct object* parse_object_buffer (int /*<<< orphan*/ ,struct object_id const*,int,unsigned long,void*,int*) ; 
 scalar_t__ read_loose_object (char const*,struct object_id const*,int*,unsigned long*,void**) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int fsck_loose(const struct object_id *oid, const char *path, void *data)
{
	struct object *obj;
	enum object_type type;
	unsigned long size;
	void *contents;
	int eaten;

	if (read_loose_object(path, oid, &type, &size, &contents) < 0) {
		errors_found |= ERROR_OBJECT;
		error(_("%s: object corrupt or missing: %s"),
		      oid_to_hex(oid), path);
		return 0; /* keep checking other objects */
	}

	if (!contents && type != OBJ_BLOB)
		BUG("read_loose_object streamed a non-blob");

	obj = parse_object_buffer(the_repository, oid, type, size,
				  contents, &eaten);

	if (!obj) {
		errors_found |= ERROR_OBJECT;
		error(_("%s: object could not be parsed: %s"),
		      oid_to_hex(oid), path);
		if (!eaten)
			free(contents);
		return 0; /* keep checking other objects */
	}

	obj->flags &= ~(REACHABLE | SEEN);
	obj->flags |= HAS_OBJ;
	if (fsck_obj(obj, contents, size))
		errors_found |= ERROR_OBJECT;

	if (!eaten)
		free(contents);
	return 0; /* keep checking other objects, even if we saw an error */
}