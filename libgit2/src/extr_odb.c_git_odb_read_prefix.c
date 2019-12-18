#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 size_t GIT_OID_HEXSZ ; 
 size_t GIT_OID_MINPREFIXLEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * git_cache_get_raw (int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int git_odb__error_ambiguous (char*) ; 
 int git_odb__error_notfound (char*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  git_odb_refresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid__cpy_prefix (TYPE_2__*,TYPE_2__ const*,size_t) ; 
 int /*<<< orphan*/  odb_cache (int /*<<< orphan*/ *) ; 
 int read_prefix_1 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_2__*,size_t,int) ; 

int git_odb_read_prefix(
	git_odb_object **out, git_odb *db, const git_oid *short_id, size_t len)
{
	git_oid key = {{0}};
	int error;

	assert(out && db);

	if (len < GIT_OID_MINPREFIXLEN)
		return git_odb__error_ambiguous("prefix length too short");

	if (len > GIT_OID_HEXSZ)
		len = GIT_OID_HEXSZ;

	if (len == GIT_OID_HEXSZ) {
		*out = git_cache_get_raw(odb_cache(db), short_id);
		if (*out != NULL)
			return 0;
	}

	git_oid__cpy_prefix(&key, short_id, len);

	error = read_prefix_1(out, db, &key, len, false);

	if (error == GIT_ENOTFOUND && !git_odb_refresh(db))
		error = read_prefix_1(out, db, &key, len, true);

	if (error == GIT_ENOTFOUND)
		return git_odb__error_notfound("no match for prefix", &key, len);

	return error;
}