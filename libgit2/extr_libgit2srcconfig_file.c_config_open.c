#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config_level_t ;
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_4__ {int /*<<< orphan*/ * entries; int /*<<< orphan*/  const* repo; int /*<<< orphan*/  level; } ;
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
struct TYPE_5__ {TYPE_1__ header; TYPE_3__ file; } ;
typedef  TYPE_2__ diskfile_backend ;

/* Variables and functions */
 int config_read (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ *) ; 
 int git_config_entries_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_open(git_config_backend *cfg, git_config_level_t level, const git_repository *repo)
{
	int res;
	diskfile_backend *b = (diskfile_backend *)cfg;

	b->header.level = level;
	b->header.repo = repo;

	if ((res = git_config_entries_new(&b->header.entries)) < 0)
		return res;

	if (!git_path_exists(b->file.path))
		return 0;

	if (res < 0 || (res = config_read(b->header.entries, repo, &b->file, level, 0)) < 0) {
		git_config_entries_free(b->header.entries);
		b->header.entries = NULL;
	}

	return res;
}