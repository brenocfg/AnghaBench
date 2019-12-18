#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ const git_oid ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 size_t GIT_OID_HEXSZ ; 
 size_t GIT_OID_MINPREFIXLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_odb__error_ambiguous (char*) ; 
 int git_odb__error_notfound (char*,TYPE_2__ const*,size_t) ; 
 scalar_t__ git_odb_exists (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  git_odb_refresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid__cpy_prefix (TYPE_2__ const*,TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  git_oid_cpy (TYPE_2__ const*,TYPE_2__ const*) ; 
 int odb_exists_prefix_1 (TYPE_2__ const*,int /*<<< orphan*/ *,TYPE_2__ const*,size_t,int) ; 

int git_odb_exists_prefix(
	git_oid *out, git_odb *db, const git_oid *short_id, size_t len)
{
	int error;
	git_oid key = {{0}};

	assert(db && short_id);

	if (len < GIT_OID_MINPREFIXLEN)
		return git_odb__error_ambiguous("prefix length too short");

	if (len >= GIT_OID_HEXSZ) {
		if (git_odb_exists(db, short_id)) {
			if (out)
				git_oid_cpy(out, short_id);
			return 0;
		} else {
			return git_odb__error_notfound(
				"no match for id prefix", short_id, len);
		}
	}

	git_oid__cpy_prefix(&key, short_id, len);

	error = odb_exists_prefix_1(out, db, &key, len, false);

	if (error == GIT_ENOTFOUND && !git_odb_refresh(db))
		error = odb_exists_prefix_1(out, db, &key, len, true);

	if (error == GIT_ENOTFOUND)
		return git_odb__error_notfound("no match for id prefix", &key, len);

	return error;
}