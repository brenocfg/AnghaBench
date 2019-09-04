#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_backend ;
struct TYPE_9__ {int /*<<< orphan*/  free; int /*<<< orphan*/  unlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  iterator; int /*<<< orphan*/  del_multivar; int /*<<< orphan*/  del; int /*<<< orphan*/  set_multivar; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  open; int /*<<< orphan*/  version; } ;
struct TYPE_10__ {TYPE_2__ parent; int /*<<< orphan*/  values_mutex; } ;
struct TYPE_8__ {int /*<<< orphan*/  includes; TYPE_4__* path; } ;
struct TYPE_11__ {TYPE_3__ header; TYPE_1__ file; } ;
typedef  TYPE_4__ diskfile_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_BACKEND_VERSION ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_4__*) ; 
 int /*<<< orphan*/  backend_free ; 
 int /*<<< orphan*/  config_delete ; 
 int /*<<< orphan*/  config_delete_multivar ; 
 int /*<<< orphan*/  config_get ; 
 int /*<<< orphan*/  config_iterator_new ; 
 int /*<<< orphan*/  config_lock ; 
 int /*<<< orphan*/  config_open ; 
 int /*<<< orphan*/  config_set ; 
 int /*<<< orphan*/  config_set_multivar ; 
 int /*<<< orphan*/  config_snapshot ; 
 int /*<<< orphan*/  config_unlock ; 
 TYPE_4__* git__calloc (int,int) ; 
 TYPE_4__* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_array_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mutex_init (int /*<<< orphan*/ *) ; 

int git_config_backend_from_file(git_config_backend **out, const char *path)
{
	diskfile_backend *backend;

	backend = git__calloc(1, sizeof(diskfile_backend));
	GIT_ERROR_CHECK_ALLOC(backend);

	backend->header.parent.version = GIT_CONFIG_BACKEND_VERSION;
	git_mutex_init(&backend->header.values_mutex);

	backend->file.path = git__strdup(path);
	GIT_ERROR_CHECK_ALLOC(backend->file.path);
	git_array_init(backend->file.includes);

	backend->header.parent.open = config_open;
	backend->header.parent.get = config_get;
	backend->header.parent.set = config_set;
	backend->header.parent.set_multivar = config_set_multivar;
	backend->header.parent.del = config_delete;
	backend->header.parent.del_multivar = config_delete_multivar;
	backend->header.parent.iterator = config_iterator_new;
	backend->header.parent.snapshot = config_snapshot;
	backend->header.parent.lock = config_lock;
	backend->header.parent.unlock = config_unlock;
	backend->header.parent.free = backend_free;

	*out = (git_config_backend *)backend;

	return 0;
}