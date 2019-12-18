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
struct oidset_iter {int dummy; } ;
struct object_id {int dummy; } ;
struct object {int /*<<< orphan*/  oid; } ;
struct fsck_options {int dummy; } ;
struct blob {struct object object; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  FSCK_MSG_GITMODULES_BLOB ; 
 int /*<<< orphan*/  FSCK_MSG_GITMODULES_MISSING ; 
 int OBJ_BLOB ; 
 int /*<<< orphan*/  free (char*) ; 
 int fsck_blob (struct blob*,char*,unsigned long,struct fsck_options*) ; 
 int /*<<< orphan*/  gitmodules_done ; 
 int /*<<< orphan*/  gitmodules_found ; 
 scalar_t__ is_promisor_object (int /*<<< orphan*/ *) ; 
 struct blob* lookup_blob (int /*<<< orphan*/ ,struct object_id const*) ; 
 struct object* lookup_unknown_object (struct object_id const*) ; 
 int /*<<< orphan*/  oidset_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ oidset_contains (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  oidset_iter_init (int /*<<< orphan*/ *,struct oidset_iter*) ; 
 struct object_id* oidset_iter_next (struct oidset_iter*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int report (struct fsck_options*,struct object*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  the_repository ; 

int fsck_finish(struct fsck_options *options)
{
	int ret = 0;
	struct oidset_iter iter;
	const struct object_id *oid;

	oidset_iter_init(&gitmodules_found, &iter);
	while ((oid = oidset_iter_next(&iter))) {
		struct blob *blob;
		enum object_type type;
		unsigned long size;
		char *buf;

		if (oidset_contains(&gitmodules_done, oid))
			continue;

		blob = lookup_blob(the_repository, oid);
		if (!blob) {
			struct object *obj = lookup_unknown_object(oid);
			ret |= report(options, obj,
				      FSCK_MSG_GITMODULES_BLOB,
				      "non-blob found at .gitmodules");
			continue;
		}

		buf = read_object_file(oid, &type, &size);
		if (!buf) {
			if (is_promisor_object(&blob->object.oid))
				continue;
			ret |= report(options, &blob->object,
				      FSCK_MSG_GITMODULES_MISSING,
				      "unable to read .gitmodules blob");
			continue;
		}

		if (type == OBJ_BLOB)
			ret |= fsck_blob(blob, buf, size, options);
		else
			ret |= report(options, &blob->object,
				      FSCK_MSG_GITMODULES_BLOB,
				      "non-blob found at .gitmodules");
		free(buf);
	}


	oidset_clear(&gitmodules_found);
	oidset_clear(&gitmodules_done);
	return ret;
}