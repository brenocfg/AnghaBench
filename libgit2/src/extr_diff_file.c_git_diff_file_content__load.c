#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flags; } ;
typedef  TYPE_2__ git_diff_options ;
struct TYPE_13__ {int flags; scalar_t__ src; TYPE_1__* file; } ;
typedef  TYPE_3__ git_diff_file_content ;
struct TYPE_11__ {int flags; } ;

/* Variables and functions */
 int GIT_DIFF_FLAG_BINARY ; 
 int GIT_DIFF_FLAG__LOADED ; 
 int GIT_DIFF_SHOW_BINARY ; 
 scalar_t__ GIT_ITERATOR_TYPE_WORKDIR ; 
 int /*<<< orphan*/  diff_file_content_binary_by_content (TYPE_3__*) ; 
 int diff_file_content_load_blob (TYPE_3__*,TYPE_2__*) ; 
 int diff_file_content_load_workdir (TYPE_3__*,TYPE_2__*) ; 

int git_diff_file_content__load(
	git_diff_file_content *fc,
	git_diff_options *diff_opts)
{
	int error = 0;

	if ((fc->flags & GIT_DIFF_FLAG__LOADED) != 0)
		return 0;

	if ((fc->file->flags & GIT_DIFF_FLAG_BINARY) != 0 &&
		(diff_opts->flags & GIT_DIFF_SHOW_BINARY) == 0)
		return 0;

	if (fc->src == GIT_ITERATOR_TYPE_WORKDIR)
		error = diff_file_content_load_workdir(fc, diff_opts);
	else
		error = diff_file_content_load_blob(fc, diff_opts);
	if (error)
		return error;

	fc->flags |= GIT_DIFF_FLAG__LOADED;

	diff_file_content_binary_by_content(fc);

	return 0;
}