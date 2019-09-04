#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ id_abbrev; scalar_t__ mode; int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {scalar_t__ id_abbrev; scalar_t__ mode; int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {scalar_t__ status; scalar_t__ flags; scalar_t__ similarity; scalar_t__ nfiles; TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 scalar_t__ num_modified_deltas (int /*<<< orphan*/ *) ; 

void diff_assert_equal(git_diff *a, git_diff *b)
{
	const git_diff_delta *ad, *bd;
	size_t i, j;

	assert(a && b);

	cl_assert_equal_i(num_modified_deltas(a), num_modified_deltas(b));

	for (i = 0, j = 0;
		i < git_diff_num_deltas(a) && j < git_diff_num_deltas(b); ) {

		ad = git_diff_get_delta(a, i);
		bd = git_diff_get_delta(b, j);

		if (ad->status == GIT_DELTA_UNMODIFIED) {
			i++;
			continue;
		}
		if (bd->status == GIT_DELTA_UNMODIFIED) {
			j++;
			continue;
		}

		cl_assert_equal_i(ad->status, bd->status);
		cl_assert_equal_i(ad->flags, bd->flags);
		cl_assert_equal_i(ad->similarity, bd->similarity);
		cl_assert_equal_i(ad->nfiles, bd->nfiles);

		/* Don't examine the size or the flags of the deltas;
		 * computed deltas have sizes (parsed deltas do not) and
		 * computed deltas will have flags of `VALID_ID` and
		 * `EXISTS` (parsed deltas will not query the ODB.)
		 */

		/* an empty id indicates that it wasn't presented, because
		 * the diff was identical.  (eg, pure rename, mode change only, etc)
		 */
		if (ad->old_file.id_abbrev && bd->old_file.id_abbrev) {
			cl_assert_equal_i(ad->old_file.id_abbrev, bd->old_file.id_abbrev);
			cl_assert_equal_oid(&ad->old_file.id, &bd->old_file.id);
			cl_assert_equal_i(ad->old_file.mode, bd->old_file.mode);
		}
		cl_assert_equal_s(ad->old_file.path, bd->old_file.path);

		if (ad->new_file.id_abbrev && bd->new_file.id_abbrev) {
			cl_assert_equal_oid(&ad->new_file.id, &bd->new_file.id);
			cl_assert_equal_i(ad->new_file.id_abbrev, bd->new_file.id_abbrev);
			cl_assert_equal_i(ad->new_file.mode, bd->new_file.mode);
		}
		cl_assert_equal_s(ad->new_file.path, bd->new_file.path);

		i++;
		j++;
	}
}