#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_1__ cached; } ;
typedef  TYPE_2__ git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int GIT_PASSTHROUGH ; 
 int error_null_oid (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* git_cache_get_raw (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_odb_object_free (TYPE_2__*) ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  odb_cache (int /*<<< orphan*/ *) ; 
 int odb_read_1 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int odb_read_header_1 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int odb_otype_fast(git_object_t *type_p, git_odb *db, const git_oid *id)
{
	git_odb_object *object;
	size_t _unused;
	int error;

	if (git_oid_is_zero(id))
		return error_null_oid(GIT_ENOTFOUND, "cannot get object type");

	if ((object = git_cache_get_raw(odb_cache(db), id)) != NULL) {
		*type_p = object->cached.type;
		git_odb_object_free(object);
		return 0;
	}

	error = odb_read_header_1(&_unused, type_p, db, id, false);

	if (error == GIT_PASSTHROUGH) {
		error = odb_read_1(&object, db, id, false);
		if (!error)
			*type_p = object->cached.type;
		git_odb_object_free(object);
	}

	return error;
}