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
struct stat {int /*<<< orphan*/  st_mtime; } ;
struct object_id {int dummy; } ;
struct object {int flags; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int SEEN ; 
 int /*<<< orphan*/  add_recent_object (struct object_id const*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ errno ; 
 int error_errno (char*,int /*<<< orphan*/ ) ; 
 struct object* lookup_object (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int add_recent_loose(const struct object_id *oid,
			    const char *path, void *data)
{
	struct stat st;
	struct object *obj = lookup_object(the_repository, oid);

	if (obj && obj->flags & SEEN)
		return 0;

	if (stat(path, &st) < 0) {
		/*
		 * It's OK if an object went away during our iteration; this
		 * could be due to a simultaneous repack. But anything else
		 * we should abort, since we might then fail to mark objects
		 * which should not be pruned.
		 */
		if (errno == ENOENT)
			return 0;
		return error_errno("unable to stat %s", oid_to_hex(oid));
	}

	add_recent_object(oid, st.st_mtime, data);
	return 0;
}