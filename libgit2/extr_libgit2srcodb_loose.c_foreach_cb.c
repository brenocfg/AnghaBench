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
struct foreach_state {int dummy; } ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_object_dir_cb ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct foreach_state*) ; 
 int /*<<< orphan*/  git_path_isdir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int foreach_cb(void *_state, git_buf *path)
{
	struct foreach_state *state = (struct foreach_state *) _state;

	/* non-dir is some stray file, ignore it */
	if (!git_path_isdir(git_buf_cstr(path)))
		return 0;

	return git_path_direach(path, 0, foreach_object_dir_cb, state);
}