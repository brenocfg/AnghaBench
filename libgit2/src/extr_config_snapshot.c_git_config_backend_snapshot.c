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
struct TYPE_7__ {int readonly; int (* snapshot ) (TYPE_1__**,TYPE_1__*) ;int /*<<< orphan*/  free; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  iterator; int /*<<< orphan*/  del_multivar; int /*<<< orphan*/  del; int /*<<< orphan*/  set_multivar; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  open; void* version; } ;
typedef  TYPE_1__ git_config_backend ;
struct TYPE_8__ {TYPE_1__ parent; TYPE_1__* source; int /*<<< orphan*/  values_mutex; } ;
typedef  TYPE_2__ config_snapshot_backend ;

/* Variables and functions */
 void* GIT_CONFIG_BACKEND_VERSION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  config_snapshot_delete ; 
 int /*<<< orphan*/  config_snapshot_delete_multivar ; 
 int /*<<< orphan*/  config_snapshot_free ; 
 int /*<<< orphan*/  config_snapshot_get ; 
 int /*<<< orphan*/  config_snapshot_iterator ; 
 int /*<<< orphan*/  config_snapshot_lock ; 
 int /*<<< orphan*/  config_snapshot_open ; 
 int /*<<< orphan*/  config_snapshot_set ; 
 int /*<<< orphan*/  config_snapshot_set_multivar ; 
 int /*<<< orphan*/  config_snapshot_unlock ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_mutex_init (int /*<<< orphan*/ *) ; 

int git_config_backend_snapshot(git_config_backend **out, git_config_backend *source)
{
	config_snapshot_backend *backend;

	backend = git__calloc(1, sizeof(config_snapshot_backend));
	GIT_ERROR_CHECK_ALLOC(backend);

	backend->parent.version = GIT_CONFIG_BACKEND_VERSION;
	git_mutex_init(&backend->values_mutex);

	backend->source = source;

	backend->parent.readonly = 1;
	backend->parent.version = GIT_CONFIG_BACKEND_VERSION;
	backend->parent.open = config_snapshot_open;
	backend->parent.get = config_snapshot_get;
	backend->parent.set = config_snapshot_set;
	backend->parent.set_multivar = config_snapshot_set_multivar;
	backend->parent.snapshot = git_config_backend_snapshot;
	backend->parent.del = config_snapshot_delete;
	backend->parent.del_multivar = config_snapshot_delete_multivar;
	backend->parent.iterator = config_snapshot_iterator;
	backend->parent.lock = config_snapshot_lock;
	backend->parent.unlock = config_snapshot_unlock;
	backend->parent.free = config_snapshot_free;

	*out = &backend->parent;

	return 0;
}