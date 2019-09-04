#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_odb_object ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_merge_file_result ;
typedef  int /*<<< orphan*/  git_merge_file_options ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_merge_file_input ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_merge_file__input_from_index (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int git_repository_odb (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int merge_file__from_inputs (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/  const*) ; 

int git_merge_file_from_index(
	git_merge_file_result *out,
	git_repository *repo,
	const git_index_entry *ancestor,
	const git_index_entry *ours,
	const git_index_entry *theirs,
	const git_merge_file_options *options)
{
	git_merge_file_input *ancestor_ptr = NULL,
		ancestor_input = {0}, our_input = {0}, their_input = {0};
	git_odb *odb = NULL;
	git_odb_object *odb_object[3] = { 0 };
	int error = 0;

	assert(out && repo && ours && theirs);

	memset(out, 0x0, sizeof(git_merge_file_result));

	if ((error = git_repository_odb(&odb, repo)) < 0)
		goto done;

	if (ancestor) {
		if ((error = git_merge_file__input_from_index(
			&ancestor_input, &odb_object[0], odb, ancestor)) < 0)
			goto done;

		ancestor_ptr = &ancestor_input;
	}

	if ((error = git_merge_file__input_from_index(
			&our_input, &odb_object[1], odb, ours)) < 0 ||
		(error = git_merge_file__input_from_index(
			&their_input, &odb_object[2], odb, theirs)) < 0)
		goto done;

	error = merge_file__from_inputs(out,
		ancestor_ptr, &our_input, &their_input, options);

done:
	git_odb_object_free(odb_object[0]);
	git_odb_object_free(odb_object[1]);
	git_odb_object_free(odb_object[2]);
	git_odb_free(odb);

	return error;
}