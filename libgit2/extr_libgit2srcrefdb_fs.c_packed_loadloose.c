#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  direach_flags; int /*<<< orphan*/  gitpath; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REFS_DIR ; 
 int /*<<< orphan*/  _dirent_loose_load ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int packed_loadloose(refdb_fs_backend *backend)
{
	int error;
	git_buf refs_path = GIT_BUF_INIT;

	if (git_buf_joinpath(&refs_path, backend->gitpath, GIT_REFS_DIR) < 0)
		return -1;

	/*
	 * Load all the loose files from disk into the Packfile table.
	 * This will overwrite any old packed entries with their
	 * updated loose versions
	 */
	error = git_path_direach(
		&refs_path, backend->direach_flags, _dirent_loose_load, backend);

	git_buf_dispose(&refs_path);

	return error;
}