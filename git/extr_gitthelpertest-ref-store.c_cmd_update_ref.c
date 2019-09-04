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
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 unsigned int arg_flags (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 int refs_update_ref (struct ref_store*,char const*,char const*,struct object_id*,struct object_id*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_update_ref(struct ref_store *refs, const char **argv)
{
	const char *msg = notnull(*argv++, "msg");
	const char *refname = notnull(*argv++, "refname");
	const char *new_sha1_buf = notnull(*argv++, "new-sha1");
	const char *old_sha1_buf = notnull(*argv++, "old-sha1");
	unsigned int flags = arg_flags(*argv++, "flags");
	struct object_id old_oid;
	struct object_id new_oid;

	if (get_oid_hex(old_sha1_buf, &old_oid) ||
	    get_oid_hex(new_sha1_buf, &new_oid))
		die("not sha-1");

	return refs_update_ref(refs, msg, refname,
			       &new_oid, &old_oid,
			       flags, UPDATE_REFS_DIE_ON_ERR);
}