#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_7__ {int /*<<< orphan*/  objects; TYPE_4__ reserved_names; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_array_init_to_size (TYPE_4__,int) ; 
 int /*<<< orphan*/  git_cache_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_cache_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup_cache_clear (TYPE_1__*) ; 

__attribute__((used)) static git_repository *repository_alloc(void)
{
	git_repository *repo = git__calloc(1, sizeof(git_repository));

	if (repo == NULL ||
		git_cache_init(&repo->objects) < 0)
		goto on_error;

	git_array_init_to_size(repo->reserved_names, 4);
	if (!repo->reserved_names.ptr)
		goto on_error;

	/* set all the entries in the configmap cache to `unset` */
	git_repository__configmap_lookup_cache_clear(repo);

	return repo;

on_error:
	if (repo)
		git_cache_dispose(&repo->objects);

	git__free(repo);
	return NULL;
}