#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/  repo; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_printf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int git_config_get_string (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_config_snapshot (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int submodule_repo_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

int git_submodule_repo_init(
	git_repository **out,
	const git_submodule *sm,
	int use_gitlink)
{
	int error;
	git_repository *sub_repo = NULL;
	const char *configured_url;
	git_config *cfg = NULL;
	git_buf buf = GIT_BUF_INIT;

	assert(out && sm);

	/* get the configured remote url of the submodule */
	if ((error = git_buf_printf(&buf, "submodule.%s.url", sm->name)) < 0 ||
		(error = git_repository_config_snapshot(&cfg, sm->repo)) < 0 ||
		(error = git_config_get_string(&configured_url, cfg, buf.ptr)) < 0 ||
		(error = submodule_repo_init(&sub_repo, sm->repo, sm->path, configured_url, use_gitlink)) < 0)
		goto done;

	*out = sub_repo;

done:
	git_config_free(cfg);
	git_buf_dispose(&buf);
	return error;
}