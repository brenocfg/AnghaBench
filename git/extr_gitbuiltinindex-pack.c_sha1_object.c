#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree {int /*<<< orphan*/ * buffer; } ;
struct object_id {int dummy; } ;
struct object_entry {int dummy; } ;
struct object {scalar_t__ type; int /*<<< orphan*/  flags; scalar_t__ parsed; struct object_id const oid; } ;
struct commit {int dummy; } ;
struct blob {struct object object; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_2__ {scalar_t__ have_repository; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  FLAG_CHECKED ; 
 int /*<<< orphan*/  OBJECT_INFO_QUICK ; 
 int OBJ_BLOB ; 
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TREE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_collison (struct object_entry*) ; 
 void const* detach_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ do_fsck_object ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fsck_object (struct object*,void*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsck_options ; 
 scalar_t__ fsck_walk (struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* get_data_from_pack (struct object_entry*) ; 
 int has_object_file_with_flags (struct object_id const*,int /*<<< orphan*/ ) ; 
 struct blob* lookup_blob (int /*<<< orphan*/ ,struct object_id const*) ; 
 scalar_t__ memcmp (void const*,void*,unsigned long) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,unsigned long*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct object* parse_object_buffer (int /*<<< orphan*/ ,struct object_id const*,int,unsigned long,void*,int*) ; 
 int /*<<< orphan*/  read_lock () ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  read_unlock () ; 
 TYPE_1__* startup_info ; 
 scalar_t__ strict ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  type_name (int) ; 

__attribute__((used)) static void sha1_object(const void *data, struct object_entry *obj_entry,
			unsigned long size, enum object_type type,
			const struct object_id *oid)
{
	void *new_data = NULL;
	int collision_test_needed = 0;

	assert(data || obj_entry);

	if (startup_info->have_repository) {
		read_lock();
		collision_test_needed =
			has_object_file_with_flags(oid, OBJECT_INFO_QUICK);
		read_unlock();
	}

	if (collision_test_needed && !data) {
		read_lock();
		if (!check_collison(obj_entry))
			collision_test_needed = 0;
		read_unlock();
	}
	if (collision_test_needed) {
		void *has_data;
		enum object_type has_type;
		unsigned long has_size;
		read_lock();
		has_type = oid_object_info(the_repository, oid, &has_size);
		if (has_type < 0)
			die(_("cannot read existing object info %s"), oid_to_hex(oid));
		if (has_type != type || has_size != size)
			die(_("SHA1 COLLISION FOUND WITH %s !"), oid_to_hex(oid));
		has_data = read_object_file(oid, &has_type, &has_size);
		read_unlock();
		if (!data)
			data = new_data = get_data_from_pack(obj_entry);
		if (!has_data)
			die(_("cannot read existing object %s"), oid_to_hex(oid));
		if (size != has_size || type != has_type ||
		    memcmp(data, has_data, size) != 0)
			die(_("SHA1 COLLISION FOUND WITH %s !"), oid_to_hex(oid));
		free(has_data);
	}

	if (strict || do_fsck_object) {
		read_lock();
		if (type == OBJ_BLOB) {
			struct blob *blob = lookup_blob(the_repository, oid);
			if (blob)
				blob->object.flags |= FLAG_CHECKED;
			else
				die(_("invalid blob object %s"), oid_to_hex(oid));
			if (do_fsck_object &&
			    fsck_object(&blob->object, (void *)data, size, &fsck_options))
				die(_("fsck error in packed object"));
		} else {
			struct object *obj;
			int eaten;
			void *buf = (void *) data;

			assert(data && "data can only be NULL for large _blobs_");

			/*
			 * we do not need to free the memory here, as the
			 * buf is deleted by the caller.
			 */
			obj = parse_object_buffer(the_repository, oid, type,
						  size, buf,
						  &eaten);
			if (!obj)
				die(_("invalid %s"), type_name(type));
			if (do_fsck_object &&
			    fsck_object(obj, buf, size, &fsck_options))
				die(_("fsck error in packed object"));
			if (strict && fsck_walk(obj, NULL, &fsck_options))
				die(_("Not all child objects of %s are reachable"), oid_to_hex(&obj->oid));

			if (obj->type == OBJ_TREE) {
				struct tree *item = (struct tree *) obj;
				item->buffer = NULL;
				obj->parsed = 0;
			}
			if (obj->type == OBJ_COMMIT) {
				struct commit *commit = (struct commit *) obj;
				if (detach_commit_buffer(commit, NULL) != data)
					BUG("parse_object_buffer transmogrified our buffer");
			}
			obj->flags |= FLAG_CHECKED;
		}
		read_unlock();
	}

	free(new_data);
}