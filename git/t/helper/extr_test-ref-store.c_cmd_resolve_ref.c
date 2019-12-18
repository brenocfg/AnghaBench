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
 int arg_flags (int /*<<< orphan*/ ,char*) ; 
 char* notnull (int /*<<< orphan*/ ,char*) ; 
 char* oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  printf (char*,char*,char const*,int) ; 
 char* refs_resolve_ref_unsafe (struct ref_store*,char const*,int,struct object_id*,int*) ; 

__attribute__((used)) static int cmd_resolve_ref(struct ref_store *refs, const char **argv)
{
	struct object_id oid;
	const char *refname = notnull(*argv++, "refname");
	int resolve_flags = arg_flags(*argv++, "resolve-flags");
	int flags;
	const char *ref;

	ref = refs_resolve_ref_unsafe(refs, refname, resolve_flags,
				      &oid, &flags);
	printf("%s %s 0x%x\n", oid_to_hex(&oid), ref ? ref : "(null)", flags);
	return ref ? 0 : 1;
}