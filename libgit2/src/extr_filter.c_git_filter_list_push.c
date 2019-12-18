#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  filters; } ;
typedef  TYPE_1__ git_filter_list ;
struct TYPE_11__ {void* payload; int /*<<< orphan*/ * filter; } ;
typedef  TYPE_2__ git_filter_entry ;
struct TYPE_12__ {int /*<<< orphan*/  initialized; } ;
typedef  TYPE_3__ git_filter_def ;
typedef  int /*<<< orphan*/  git_filter ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_ERROR_FILTER ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  filter_def_filter_key_check ; 
 int filter_initialize (TYPE_3__*) ; 
 TYPE_7__ filter_registry ; 
 TYPE_2__* git_array_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_rdunlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ git_vector_search2 (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_filter_list_push(
	git_filter_list *fl, git_filter *filter, void *payload)
{
	int error = 0;
	size_t pos;
	git_filter_def *fdef = NULL;
	git_filter_entry *fe;

	assert(fl && filter);

	if (git_rwlock_rdlock(&filter_registry.lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock filter registry");
		return -1;
	}

	if (git_vector_search2(
			&pos, &filter_registry.filters,
			filter_def_filter_key_check, filter) == 0)
		fdef = git_vector_get(&filter_registry.filters, pos);

	git_rwlock_rdunlock(&filter_registry.lock);

	if (fdef == NULL) {
		git_error_set(GIT_ERROR_FILTER, "cannot use an unregistered filter");
		return -1;
	}

	if (!fdef->initialized && (error = filter_initialize(fdef)) < 0)
		return error;

	fe = git_array_alloc(fl->filters);
	GIT_ERROR_CHECK_ALLOC(fe);
	fe->filter  = filter;
	fe->payload = payload;

	return 0;
}