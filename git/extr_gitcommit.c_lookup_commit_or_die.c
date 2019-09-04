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
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oideq (struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

struct commit *lookup_commit_or_die(const struct object_id *oid, const char *ref_name)
{
	struct commit *c = lookup_commit_reference(the_repository, oid);
	if (!c)
		die(_("could not parse %s"), ref_name);
	if (!oideq(oid, &c->object.oid)) {
		warning(_("%s %s is not a commit!"),
			ref_name, oid_to_hex(oid));
	}
	return c;
}