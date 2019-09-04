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
 unsigned int arg_flags (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 int refs_delete_ref (struct ref_store*,char const*,char const*,struct object_id*,unsigned int) ; 

__attribute__((used)) static int cmd_delete_ref(struct ref_store *refs, const char **argv)
{
	const char *msg = notnull(*argv++, "msg");
	const char *refname = notnull(*argv++, "refname");
	const char *sha1_buf = notnull(*argv++, "old-sha1");
	unsigned int flags = arg_flags(*argv++, "flags");
	struct object_id old_oid;

	if (get_oid_hex(sha1_buf, &old_oid))
		die("not sha-1");

	return refs_delete_ref(refs, msg, refname, &old_oid, flags);
}