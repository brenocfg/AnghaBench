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
 struct ref_store* get_submodule_ref_store (char const*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 int /*<<< orphan*/  refs_resolve_ref_unsafe (struct ref_store*,char const*,int /*<<< orphan*/ ,struct object_id*,int*) ; 

int resolve_gitlink_ref(const char *submodule, const char *refname,
			struct object_id *oid)
{
	struct ref_store *refs;
	int flags;

	refs = get_submodule_ref_store(submodule);

	if (!refs)
		return -1;

	if (!refs_resolve_ref_unsafe(refs, refname, 0, oid, &flags) ||
	    is_null_oid(oid))
		return -1;
	return 0;
}