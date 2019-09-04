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
struct repository {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_COMMIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,...) ; 
 void* get_cached_commit_buffer (struct repository*,struct commit const*,unsigned long*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 void* repo_read_object_file (struct repository*,int /*<<< orphan*/ *,int*,unsigned long*) ; 
 int /*<<< orphan*/  type_name (int) ; 

const void *repo_get_commit_buffer(struct repository *r,
				   const struct commit *commit,
				   unsigned long *sizep)
{
	const void *ret = get_cached_commit_buffer(r, commit, sizep);
	if (!ret) {
		enum object_type type;
		unsigned long size;
		ret = repo_read_object_file(r, &commit->object.oid, &type, &size);
		if (!ret)
			die("cannot read commit object %s",
			    oid_to_hex(&commit->object.oid));
		if (type != OBJ_COMMIT)
			die("expected commit for %s, got %s",
			    oid_to_hex(&commit->object.oid), type_name(type));
		if (sizep)
			*sizep = size;
	}
	return ret;
}