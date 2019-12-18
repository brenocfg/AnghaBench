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
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_oid_committish (char const*,struct object_id*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  the_repository ; 

struct commit *lookup_commit_reference_by_name(const char *name)
{
	struct object_id oid;
	struct commit *commit;

	if (get_oid_committish(name, &oid))
		return NULL;
	commit = lookup_commit_reference(the_repository, &oid);
	if (parse_commit(commit))
		return NULL;
	return commit;
}