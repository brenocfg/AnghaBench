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
struct pack_backend {int /*<<< orphan*/  pack_folder; } ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_joinpath (int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ git_path_isdir (int /*<<< orphan*/ ) ; 
 scalar_t__ pack_backend__alloc (struct pack_backend**,int) ; 
 int /*<<< orphan*/  pack_backend__free (int /*<<< orphan*/ *) ; 
 int pack_backend__refresh (int /*<<< orphan*/ *) ; 

int git_odb_backend_pack(git_odb_backend **backend_out, const char *objects_dir)
{
	int error = 0;
	struct pack_backend *backend = NULL;
	git_buf path = GIT_BUF_INIT;

	if (pack_backend__alloc(&backend, 8) < 0)
		return -1;

	if (!(error = git_buf_joinpath(&path, objects_dir, "pack")) &&
		git_path_isdir(git_buf_cstr(&path)))
	{
		backend->pack_folder = git_buf_detach(&path);
		error = pack_backend__refresh((git_odb_backend *)backend);
	}

	if (error < 0) {
		pack_backend__free((git_odb_backend *)backend);
		backend = NULL;
	}

	*backend_out = (git_odb_backend *)backend;

	git_buf_dispose(&path);

	return error;
}