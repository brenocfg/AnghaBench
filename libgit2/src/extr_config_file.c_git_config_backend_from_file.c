#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_8__ {int /*<<< orphan*/  free; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  iterator; int /*<<< orphan*/  del_multivar; int /*<<< orphan*/  del; int /*<<< orphan*/  set_multivar; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  open; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {int /*<<< orphan*/  includes; TYPE_3__* path; } ;
struct TYPE_9__ {TYPE_2__ parent; TYPE_1__ file; int /*<<< orphan*/  values_mutex; } ;
typedef  TYPE_3__ config_file_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_BACKEND_VERSION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_3__*) ; 
 int /*<<< orphan*/  config_file_delete ; 
 int /*<<< orphan*/  config_file_delete_multivar ; 
 int /*<<< orphan*/  config_file_free ; 
 int /*<<< orphan*/  config_file_get ; 
 int /*<<< orphan*/  config_file_iterator ; 
 int /*<<< orphan*/  config_file_lock ; 
 int /*<<< orphan*/  config_file_open ; 
 int /*<<< orphan*/  config_file_set ; 
 int /*<<< orphan*/  config_file_set_multivar ; 
 int /*<<< orphan*/  config_file_snapshot ; 
 int /*<<< orphan*/  config_file_unlock ; 
 TYPE_3__* git__calloc (int,int) ; 
 TYPE_3__* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_array_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mutex_init (int /*<<< orphan*/ *) ; 

int git_config_backend_from_file(git_config_backend **out, const char *path)
{
	config_file_backend *backend;

	backend = git__calloc(1, sizeof(config_file_backend));
	GIT_ERROR_CHECK_ALLOC(backend);

	backend->parent.version = GIT_CONFIG_BACKEND_VERSION;
	git_mutex_init(&backend->values_mutex);

	backend->file.path = git__strdup(path);
	GIT_ERROR_CHECK_ALLOC(backend->file.path);
	git_array_init(backend->file.includes);

	backend->parent.open = config_file_open;
	backend->parent.get = config_file_get;
	backend->parent.set = config_file_set;
	backend->parent.set_multivar = config_file_set_multivar;
	backend->parent.del = config_file_delete;
	backend->parent.del_multivar = config_file_delete_multivar;
	backend->parent.iterator = config_file_iterator;
	backend->parent.snapshot = config_file_snapshot;
	backend->parent.lock = config_file_lock;
	backend->parent.unlock = config_file_unlock;
	backend->parent.free = config_file_free;

	*out = (git_config_backend *)backend;

	return 0;
}