#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct foreach_state {int /*<<< orphan*/  dir_len; void* data; scalar_t__ cb; } ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_2__ {char* objects_dir; } ;
typedef  TYPE_1__ loose_backend ;
typedef  scalar_t__ git_odb_foreach_cb ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  foreach_cb ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_len (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char*) ; 
 int git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct foreach_state*) ; 
 int /*<<< orphan*/  git_path_to_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct foreach_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int loose_backend__foreach(git_odb_backend *_backend, git_odb_foreach_cb cb, void *data)
{
	char *objects_dir;
	int error;
	git_buf buf = GIT_BUF_INIT;
	struct foreach_state state;
	loose_backend *backend = (loose_backend *) _backend;

	assert(backend && cb);

	objects_dir = backend->objects_dir;

	git_buf_sets(&buf, objects_dir);
	git_path_to_dir(&buf);
	if (git_buf_oom(&buf))
		return -1;

	memset(&state, 0, sizeof(state));
	state.cb = cb;
	state.data = data;
	state.dir_len = git_buf_len(&buf);

	error = git_path_direach(&buf, 0, foreach_cb, &state);

	git_buf_dispose(&buf);

	return error;
}