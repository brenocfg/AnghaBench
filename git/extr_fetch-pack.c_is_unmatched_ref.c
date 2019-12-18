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
struct ref {scalar_t__ match_status; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ REF_NOT_MATCHED ; 
 scalar_t__ oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_oid_hex (int /*<<< orphan*/ ,struct object_id*,char const**) ; 

__attribute__((used)) static int is_unmatched_ref(const struct ref *ref)
{
	struct object_id oid;
	const char *p;
	return	ref->match_status == REF_NOT_MATCHED &&
		!parse_oid_hex(ref->name, &oid, &p) &&
		*p == '\0' &&
		oideq(&oid, &ref->old_oid);
}