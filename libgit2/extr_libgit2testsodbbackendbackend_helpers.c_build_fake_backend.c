#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  fake_object ;
struct TYPE_5__ {int /*<<< orphan*/ * free; int /*<<< orphan*/  exists_prefix; int /*<<< orphan*/  exists; int /*<<< orphan*/  read_header; int /*<<< orphan*/  read_prefix; int /*<<< orphan*/  read; int /*<<< orphan*/ * refresh; int /*<<< orphan*/  version; } ;
struct TYPE_6__ {TYPE_1__ parent; int /*<<< orphan*/  const* objects; } ;
typedef  TYPE_2__ fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ODB_BACKEND_VERSION ; 
 int /*<<< orphan*/  fake_backend__exists ; 
 int /*<<< orphan*/  fake_backend__exists_prefix ; 
 int /*<<< orphan*/  fake_backend__free ; 
 int /*<<< orphan*/  fake_backend__read ; 
 int /*<<< orphan*/  fake_backend__read_header ; 
 int /*<<< orphan*/  fake_backend__read_prefix ; 
 TYPE_2__* git__calloc (int,int) ; 

int build_fake_backend(
	git_odb_backend **out,
	const fake_object *objects)
{
	fake_backend *backend;

	backend = git__calloc(1, sizeof(fake_backend));
	GIT_ERROR_CHECK_ALLOC(backend);

	backend->parent.version = GIT_ODB_BACKEND_VERSION;

	backend->parent.refresh = NULL;
	backend->objects = objects;

	backend->parent.read = fake_backend__read;
	backend->parent.read_prefix = fake_backend__read_prefix;
	backend->parent.read_header = fake_backend__read_header;
	backend->parent.exists = fake_backend__exists;
	backend->parent.exists_prefix = fake_backend__exists_prefix;
	backend->parent.free = &fake_backend__free;

	*out = (git_odb_backend *)backend;

	return 0;
}