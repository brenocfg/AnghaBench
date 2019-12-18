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
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int error_null_oid (int,char*) ; 
 int /*<<< orphan*/ * git_cache_get_raw (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_refresh (int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  odb_cache (int /*<<< orphan*/ *) ; 
 int odb_read_1 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int git_odb_read(git_odb_object **out, git_odb *db, const git_oid *id)
{
	int error;

	assert(out && db && id);

	if (git_oid_is_zero(id))
		return error_null_oid(GIT_ENOTFOUND, "cannot read object");

	*out = git_cache_get_raw(odb_cache(db), id);
	if (*out != NULL)
		return 0;

	error = odb_read_1(out, db, id, false);

	if (error == GIT_ENOTFOUND && !git_odb_refresh(db))
		error = odb_read_1(out, db, id, true);

	if (error == GIT_ENOTFOUND)
		return git_odb__error_notfound("no match for id", id, GIT_OID_HEXSZ);

	return error;
}