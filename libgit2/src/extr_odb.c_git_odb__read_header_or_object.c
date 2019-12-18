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
struct TYPE_6__ {size_t size; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_1__ cached; } ;
typedef  TYPE_2__ git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int error_null_oid (int,char*) ; 
 TYPE_2__* git_cache_get_raw (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_odb_read (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_odb_refresh (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  odb_cache (int /*<<< orphan*/ *) ; 
 int odb_read_header_1 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int git_odb__read_header_or_object(
	git_odb_object **out, size_t *len_p, git_object_t *type_p,
	git_odb *db, const git_oid *id)
{
	int error = GIT_ENOTFOUND;
	git_odb_object *object;

	assert(db && id && out && len_p && type_p);

	*out = NULL;

	if (git_oid_is_zero(id))
		return error_null_oid(GIT_ENOTFOUND, "cannot read object");

	if ((object = git_cache_get_raw(odb_cache(db), id)) != NULL) {
		*len_p = object->cached.size;
		*type_p = object->cached.type;
		*out = object;
		return 0;
	}

	error = odb_read_header_1(len_p, type_p, db, id, false);

	if (error == GIT_ENOTFOUND && !git_odb_refresh(db))
		error = odb_read_header_1(len_p, type_p, db, id, true);

	if (error == GIT_ENOTFOUND)
		return git_odb__error_notfound("cannot read header for", id, GIT_OID_HEXSZ);

	/* we found the header; return early */
	if (!error)
		return 0;

	if (error == GIT_PASSTHROUGH) {
		/*
		 * no backend has header-reading functionality
		 * so try using `git_odb_read` instead
		 */
		error = git_odb_read(&object, db, id);
		if (!error) {
			*len_p = object->cached.size;
			*type_p = object->cached.type;
			*out = object;
		}
	}

	return error;
}