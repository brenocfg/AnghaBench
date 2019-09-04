#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_merge_file_result ;
typedef  int /*<<< orphan*/  git_merge_file_options ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_merge_file_input ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* git_merge_file__normalize_inputs (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int merge_file__from_inputs (int /*<<< orphan*/ *,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 

int git_merge_file(
	git_merge_file_result *out,
	const git_merge_file_input *ancestor,
	const git_merge_file_input *ours,
	const git_merge_file_input *theirs,
	const git_merge_file_options *options)
{
	git_merge_file_input inputs[3] = { {0} };

	assert(out && ours && theirs);

	memset(out, 0x0, sizeof(git_merge_file_result));

	if (ancestor)
		ancestor = git_merge_file__normalize_inputs(&inputs[0], ancestor);

	ours = git_merge_file__normalize_inputs(&inputs[1], ours);
	theirs = git_merge_file__normalize_inputs(&inputs[2], theirs);

	return merge_file__from_inputs(out, ancestor, ours, theirs, options);
}