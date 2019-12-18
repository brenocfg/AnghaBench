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
struct object_id {int dummy; } ;
struct object {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDDEN_REF ; 
 int /*<<< orphan*/  OUR_REF ; 
 struct object* lookup_unknown_object (struct object_id const*) ; 
 scalar_t__ ref_is_hidden (char const*,char const*) ; 

__attribute__((used)) static int mark_our_ref(const char *refname, const char *refname_full,
			const struct object_id *oid)
{
	struct object *o = lookup_unknown_object(oid);

	if (ref_is_hidden(refname, refname_full)) {
		o->flags |= HIDDEN_REF;
		return 1;
	}
	o->flags |= OUR_REF;
	return 0;
}