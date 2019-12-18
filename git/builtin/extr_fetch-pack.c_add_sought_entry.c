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
struct ref {int /*<<< orphan*/  old_oid; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct ref**,int,int) ; 
 struct ref* alloc_ref (char const*) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  parse_oid_hex (char const*,struct object_id*,char const**) ; 

__attribute__((used)) static void add_sought_entry(struct ref ***sought, int *nr, int *alloc,
			     const char *name)
{
	struct ref *ref;
	struct object_id oid;
	const char *p;

	if (!parse_oid_hex(name, &oid, &p)) {
		if (*p == ' ') {
			/* <oid> <ref>, find refname */
			name = p + 1;
		} else if (*p == '\0') {
			; /* <oid>, leave oid as name */
		} else {
			/* <ref>, clear cruft from oid */
			oidclr(&oid);
		}
	} else {
		/* <ref>, clear cruft from get_oid_hex */
		oidclr(&oid);
	}

	ref = alloc_ref(name);
	oidcpy(&ref->old_oid, &oid);
	(*nr)++;
	ALLOC_GROW(*sought, *nr, *alloc);
	(*sought)[*nr - 1] = ref;
}