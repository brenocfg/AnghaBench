#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  own_cache; int /*<<< orphan*/  backends; } ;
typedef  TYPE_1__ git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_1__*) ; 
 int /*<<< orphan*/  backend_sort_cmp ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_cache_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_cache_init (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int git_odb_new(git_odb **out)
{
	git_odb *db = git__calloc(1, sizeof(*db));
	GIT_ERROR_CHECK_ALLOC(db);

	if (git_cache_init(&db->own_cache) < 0) {
		git__free(db);
		return -1;
	}
	if (git_vector_init(&db->backends, 4, backend_sort_cmp) < 0) {
		git_cache_dispose(&db->own_cache);
		git__free(db);
		return -1;
	}

	*out = db;
	GIT_REFCOUNT_INC(db);
	return 0;
}