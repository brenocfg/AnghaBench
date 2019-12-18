#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_filter ;
struct TYPE_2__ {int /*<<< orphan*/  filters; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_CRLF ; 
 int /*<<< orphan*/  GIT_FILTER_CRLF_PRIORITY ; 
 int /*<<< orphan*/  GIT_FILTER_IDENT ; 
 int /*<<< orphan*/  GIT_FILTER_IDENT_PRIORITY ; 
 int /*<<< orphan*/  filter_def_priority_cmp ; 
 TYPE_1__ filter_registry ; 
 scalar_t__ filter_registry_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__on_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_crlf_filter_new () ; 
 int /*<<< orphan*/  git_filter_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_global_shutdown ; 
 int /*<<< orphan*/ * git_ident_filter_new () ; 
 scalar_t__ git_rwlock_init (int /*<<< orphan*/ *) ; 
 int git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int git_filter_global_init(void)
{
	git_filter *crlf = NULL, *ident = NULL;
	int error = 0;

	if (git_rwlock_init(&filter_registry.lock) < 0)
		return -1;

	if ((error = git_vector_init(&filter_registry.filters, 2,
		filter_def_priority_cmp)) < 0)
		goto done;

	if ((crlf = git_crlf_filter_new()) == NULL ||
		filter_registry_insert(
			GIT_FILTER_CRLF, crlf, GIT_FILTER_CRLF_PRIORITY) < 0 ||
		(ident = git_ident_filter_new()) == NULL ||
		filter_registry_insert(
			GIT_FILTER_IDENT, ident, GIT_FILTER_IDENT_PRIORITY) < 0)
		error = -1;

	git__on_shutdown(git_filter_global_shutdown);

done:
	if (error) {
		git_filter_free(crlf);
		git_filter_free(ident);
	}

	return error;
}