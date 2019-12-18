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
struct ref {int exact_oid; struct ref* next; int /*<<< orphan*/  old_oid; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct ref* alloc_ref (int /*<<< orphan*/ ) ; 
 int fetch_refs (char const*,struct ref*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 

__attribute__((used)) static int fetch_objects(const char *remote_name,
			 const struct object_id *oids,
			 int oid_nr)
{
	struct ref *ref = NULL;
	int i;

	for (i = 0; i < oid_nr; i++) {
		struct ref *new_ref = alloc_ref(oid_to_hex(&oids[i]));
		oidcpy(&new_ref->old_oid, &oids[i]);
		new_ref->exact_oid = 1;
		new_ref->next = ref;
		ref = new_ref;
	}
	return fetch_refs(remote_name, ref);
}