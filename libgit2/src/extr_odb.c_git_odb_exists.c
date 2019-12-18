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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git_cache_get_raw (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_refresh (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  odb_cache (int /*<<< orphan*/ *) ; 
 int odb_exists_1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int git_odb_exists(git_odb *db, const git_oid *id)
{
	git_odb_object *object;

	assert(db && id);

	if (git_oid_is_zero(id))
		return 0;

	if ((object = git_cache_get_raw(odb_cache(db), id)) != NULL) {
		git_odb_object_free(object);
		return 1;
	}

	if (odb_exists_1(db, id, false))
		return 1;

	if (!git_odb_refresh(db))
		return odb_exists_1(db, id, true);

	/* Failed to refresh, hence not found */
	return 0;
}