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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct pack_backend {int /*<<< orphan*/  packs; int /*<<< orphan*/ * pack_folder; } ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pack_backend*) ; 
 int /*<<< orphan*/  git_vector_sort (int /*<<< orphan*/ *) ; 
 scalar_t__ p_stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  packfile_load__cb ; 

__attribute__((used)) static int pack_backend__refresh(git_odb_backend *backend_)
{
	int error;
	struct stat st;
	git_buf path = GIT_BUF_INIT;
	struct pack_backend *backend = (struct pack_backend *)backend_;

	if (backend->pack_folder == NULL)
		return 0;

	if (p_stat(backend->pack_folder, &st) < 0 || !S_ISDIR(st.st_mode))
		return git_odb__error_notfound("failed to refresh packfiles", NULL, 0);

	git_buf_sets(&path, backend->pack_folder);

	/* reload all packs */
	error = git_path_direach(&path, 0, packfile_load__cb, backend);

	git_buf_dispose(&path);
	git_vector_sort(&backend->packs);

	return error;
}