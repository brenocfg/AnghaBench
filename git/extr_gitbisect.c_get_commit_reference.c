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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct commit* lookup_commit_reference (struct repository*,struct object_id const*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 

__attribute__((used)) static struct commit *get_commit_reference(struct repository *r,
					   const struct object_id *oid)
{
	struct commit *c = lookup_commit_reference(r, oid);
	if (!c)
		die(_("Not a valid commit name %s"), oid_to_hex(oid));
	return c;
}