#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config_level_t ;
struct TYPE_11__ {int (* open ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_1__ git_config_backend ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_12__ {int /*<<< orphan*/  level; TYPE_1__* backend; } ;
typedef  TYPE_2__ backend_internal ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_BACKEND_VERSION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 TYPE_2__* git__malloc (int) ; 
 int git_config__add_internal (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int git_config_add_backend(
	git_config *cfg,
	git_config_backend *backend,
	git_config_level_t level,
	const git_repository *repo,
	int force)
{
	backend_internal *internal;
	int result;

	assert(cfg && backend);

	GIT_ERROR_CHECK_VERSION(backend, GIT_CONFIG_BACKEND_VERSION, "git_config_backend");

	if ((result = backend->open(backend, level, repo)) < 0)
		return result;

	internal = git__malloc(sizeof(backend_internal));
	GIT_ERROR_CHECK_ALLOC(internal);

	memset(internal, 0x0, sizeof(backend_internal));

	internal->backend = backend;
	internal->level = level;

	if ((result = git_config__add_internal(cfg, internal, level, force)) < 0) {
		git__free(internal);
		return result;
	}

	return 0;
}