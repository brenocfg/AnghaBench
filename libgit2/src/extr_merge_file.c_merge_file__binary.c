#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int automergeable; int /*<<< orphan*/  mode; int /*<<< orphan*/  len; int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ git_merge_file_result ;
struct TYPE_10__ {scalar_t__ favor; } ;
typedef  TYPE_2__ git_merge_file_options ;
struct TYPE_11__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ git_merge_file_input ;

/* Variables and functions */
 scalar_t__ GIT_MERGE_FILE_FAVOR_OURS ; 
 scalar_t__ GIT_MERGE_FILE_FAVOR_THEIRS ; 
 int /*<<< orphan*/ * git__malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

__attribute__((used)) static int merge_file__binary(
	git_merge_file_result *out,
	const git_merge_file_input *ours,
	const git_merge_file_input *theirs,
	const git_merge_file_options *given_opts)
{
	const git_merge_file_input *favored = NULL;

	memset(out, 0x0, sizeof(git_merge_file_result));

	if (given_opts && given_opts->favor == GIT_MERGE_FILE_FAVOR_OURS)
		favored = ours;
	else if (given_opts && given_opts->favor == GIT_MERGE_FILE_FAVOR_THEIRS)
		favored = theirs;
	else
		goto done;

	if ((out->path = git__strdup(favored->path)) == NULL ||
		(out->ptr = git__malloc(favored->size)) == NULL)
		goto done;

	memcpy((char *)out->ptr, favored->ptr, favored->size);
	out->len = favored->size;
	out->mode = favored->mode;
	out->automergeable = 1;

done:
	return 0;
}