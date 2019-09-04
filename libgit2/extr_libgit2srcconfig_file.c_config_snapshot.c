#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_6__ {int readonly; int /*<<< orphan*/  free; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  iterator; int /*<<< orphan*/  del_multivar; int /*<<< orphan*/  del; int /*<<< orphan*/  set_multivar; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  open; void* version; } ;
struct TYPE_7__ {TYPE_1__ parent; int /*<<< orphan*/  values_mutex; } ;
struct TYPE_8__ {TYPE_2__ header; int /*<<< orphan*/ * snapshot_from; } ;
typedef  TYPE_3__ diskfile_readonly_backend ;
typedef  int /*<<< orphan*/  diskfile_backend ;

/* Variables and functions */
 void* GIT_CONFIG_BACKEND_VERSION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_3__*) ; 
 int /*<<< orphan*/  backend_readonly_free ; 
 int /*<<< orphan*/  config_delete_multivar_readonly ; 
 int /*<<< orphan*/  config_delete_readonly ; 
 int /*<<< orphan*/  config_get ; 
 int /*<<< orphan*/  config_iterator_new ; 
 int /*<<< orphan*/  config_lock_readonly ; 
 int /*<<< orphan*/  config_readonly_open ; 
 int /*<<< orphan*/  config_set_multivar_readonly ; 
 int /*<<< orphan*/  config_set_readonly ; 
 int /*<<< orphan*/  config_unlock_readonly ; 
 TYPE_3__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_snapshot(git_config_backend **out, git_config_backend *in)
{
	diskfile_readonly_backend *backend;

	backend = git__calloc(1, sizeof(diskfile_readonly_backend));
	GIT_ERROR_CHECK_ALLOC(backend);

	backend->header.parent.version = GIT_CONFIG_BACKEND_VERSION;
	git_mutex_init(&backend->header.values_mutex);

	backend->snapshot_from = (diskfile_backend *) in;

	backend->header.parent.readonly = 1;
	backend->header.parent.version = GIT_CONFIG_BACKEND_VERSION;
	backend->header.parent.open = config_readonly_open;
	backend->header.parent.get = config_get;
	backend->header.parent.set = config_set_readonly;
	backend->header.parent.set_multivar = config_set_multivar_readonly;
	backend->header.parent.del = config_delete_readonly;
	backend->header.parent.del_multivar = config_delete_multivar_readonly;
	backend->header.parent.iterator = config_iterator_new;
	backend->header.parent.lock = config_lock_readonly;
	backend->header.parent.unlock = config_unlock_readonly;
	backend->header.parent.free = backend_readonly_free;

	*out = (git_config_backend *)backend;

	return 0;
}