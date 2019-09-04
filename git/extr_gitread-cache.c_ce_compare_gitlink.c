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
struct cache_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  oideq (struct object_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ resolve_gitlink_ref (int /*<<< orphan*/ ,char*,struct object_id*) ; 

__attribute__((used)) static int ce_compare_gitlink(const struct cache_entry *ce)
{
	struct object_id oid;

	/*
	 * We don't actually require that the .git directory
	 * under GITLINK directory be a valid git directory. It
	 * might even be missing (in case nobody populated that
	 * sub-project).
	 *
	 * If so, we consider it always to match.
	 */
	if (resolve_gitlink_ref(ce->name, "HEAD", &oid) < 0)
		return 0;
	return !oideq(&oid, &ce->oid);
}