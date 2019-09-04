#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  symbolic; int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ target; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_refdb_backend ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int git__strcmp (char const*,int /*<<< orphan*/ ) ; 
 int git_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 int refdb_fs_backend__lookup (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int cmp_old_ref(int *cmp, git_refdb_backend *backend, const char *name,
	const git_oid *old_id, const char *old_target)
{
	int error = 0;
	git_reference *old_ref = NULL;

	*cmp = 0;
	/* It "matches" if there is no old value to compare against */
	if (!old_id && !old_target)
		return 0;

	if ((error = refdb_fs_backend__lookup(&old_ref, backend, name)) < 0)
		goto out;

	/* If the types don't match, there's no way the values do */
	if (old_id && old_ref->type != GIT_REFERENCE_DIRECT) {
		*cmp = -1;
		goto out;
	}
	if (old_target && old_ref->type != GIT_REFERENCE_SYMBOLIC) {
		*cmp = 1;
		goto out;
	}

	if (old_id && old_ref->type == GIT_REFERENCE_DIRECT)
		*cmp = git_oid_cmp(old_id, &old_ref->target.oid);

	if (old_target && old_ref->type == GIT_REFERENCE_SYMBOLIC)
		*cmp = git__strcmp(old_target, old_ref->target.symbolic);

out:
	git_reference_free(old_ref);

	return error;
}