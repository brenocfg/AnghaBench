#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int initialized; struct TYPE_6__* attrdata; struct TYPE_6__* filter_name; TYPE_2__* filter; } ;
typedef  TYPE_1__ git_filter_def ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  filters; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* shutdown ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_FILTER ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_FILTER_CRLF ; 
 int /*<<< orphan*/  GIT_FILTER_IDENT ; 
 int /*<<< orphan*/  assert (char const*) ; 
 TYPE_5__ filter_registry ; 
 TYPE_1__* filter_registry_lookup (size_t*,char const*) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ git_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rwlock_wrunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_remove (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int git_filter_unregister(const char *name)
{
	size_t pos;
	git_filter_def *fdef;
	int error = 0;

	assert(name);

	/* cannot unregister default filters */
	if (!strcmp(GIT_FILTER_CRLF, name) || !strcmp(GIT_FILTER_IDENT, name)) {
		git_error_set(GIT_ERROR_FILTER, "cannot unregister filter '%s'", name);
		return -1;
	}

	if (git_rwlock_wrlock(&filter_registry.lock) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to lock filter registry");
		return -1;
	}

	if ((fdef = filter_registry_lookup(&pos, name)) == NULL) {
		git_error_set(GIT_ERROR_FILTER, "cannot find filter '%s' to unregister", name);
		error = GIT_ENOTFOUND;
		goto done;
	}

	git_vector_remove(&filter_registry.filters, pos);

	if (fdef->initialized && fdef->filter && fdef->filter->shutdown) {
		fdef->filter->shutdown(fdef->filter);
		fdef->initialized = false;
	}

	git__free(fdef->filter_name);
	git__free(fdef->attrdata);
	git__free(fdef);

done:
	git_rwlock_wrunlock(&filter_registry.lock);
	return error;
}