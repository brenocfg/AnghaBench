#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_6__ {int readonly; int /*<<< orphan*/  free; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  iterator; int /*<<< orphan*/  del_multivar; int /*<<< orphan*/  del; int /*<<< orphan*/  set_multivar; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  open; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {TYPE_1__ parent; int /*<<< orphan*/  entries; int /*<<< orphan*/  cfg; } ;
typedef  TYPE_2__ config_memory_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_BACKEND_VERSION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  config_memory_delete ; 
 int /*<<< orphan*/  config_memory_delete_multivar ; 
 int /*<<< orphan*/  config_memory_free ; 
 int /*<<< orphan*/  config_memory_get ; 
 int /*<<< orphan*/  config_memory_iterator ; 
 int /*<<< orphan*/  config_memory_lock ; 
 int /*<<< orphan*/  config_memory_open ; 
 int /*<<< orphan*/  config_memory_set ; 
 int /*<<< orphan*/  config_memory_set_multivar ; 
 int /*<<< orphan*/  config_memory_unlock ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 scalar_t__ git_buf_set (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  git_config_backend_snapshot ; 
 int /*<<< orphan*/  git_config_entries_free (int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_entries_new (int /*<<< orphan*/ *) ; 

int git_config_backend_from_string(git_config_backend **out, const char *cfg, size_t len)
{
	config_memory_backend *backend;

	backend = git__calloc(1, sizeof(config_memory_backend));
	GIT_ERROR_CHECK_ALLOC(backend);

	if (git_config_entries_new(&backend->entries) < 0) {
		git__free(backend);
		return -1;
	}

	if (git_buf_set(&backend->cfg, cfg, len) < 0) {
		git_config_entries_free(backend->entries);
		git__free(backend);
		return -1;
	}

	backend->parent.version = GIT_CONFIG_BACKEND_VERSION;
	backend->parent.readonly = 1;
	backend->parent.open = config_memory_open;
	backend->parent.get = config_memory_get;
	backend->parent.set = config_memory_set;
	backend->parent.set_multivar = config_memory_set_multivar;
	backend->parent.del = config_memory_delete;
	backend->parent.del_multivar = config_memory_delete_multivar;
	backend->parent.iterator = config_memory_iterator;
	backend->parent.lock = config_memory_lock;
	backend->parent.unlock = config_memory_unlock;
	backend->parent.snapshot = git_config_backend_snapshot;
	backend->parent.free = config_memory_free;

	*out = (git_config_backend *)backend;

	return 0;
}