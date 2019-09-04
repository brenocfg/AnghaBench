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
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; TYPE_1__ map; } ;
typedef  TYPE_2__ git_diff_file_content ;
struct TYPE_13__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__FREE_DATA ; 
 int /*<<< orphan*/  git_buf_detach (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_len (TYPE_3__*) ; 
 int git_futils_readbuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int diff_file_content_load_workdir_symlink_fake(
	git_diff_file_content *fc, git_buf *path)
{
	git_buf target = GIT_BUF_INIT;
	int error;

	if ((error = git_futils_readbuffer(&target, path->ptr)) < 0)
		return error;

	fc->map.len = git_buf_len(&target);
	fc->map.data = git_buf_detach(&target);
	fc->flags |= GIT_DIFF_FLAG__FREE_DATA;

	git_buf_dispose(&target);
	return error;
}