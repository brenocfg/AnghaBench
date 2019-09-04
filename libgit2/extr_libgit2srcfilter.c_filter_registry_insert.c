#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int priority; size_t nattrs; size_t nmatches; struct TYPE_12__* attrdata; struct TYPE_12__* filter_name; TYPE_2__* filter; } ;
typedef  TYPE_1__ git_filter_def ;
struct TYPE_13__ {int /*<<< orphan*/  attributes; } ;
typedef  TYPE_2__ git_filter ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_14__ {int /*<<< orphan*/  filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_MULTIPLY (size_t*,size_t,int) ; 
 scalar_t__ filter_def_scan_attrs (int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_def_set_attrs (TYPE_1__*) ; 
 TYPE_9__ filter_registry ; 
 TYPE_1__* git__calloc (int,size_t) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 TYPE_1__* git__strdup (char const*) ; 
 TYPE_1__* git_buf_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_sort (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_registry_insert(
	const char *name, git_filter *filter, int priority)
{
	git_filter_def *fdef;
	size_t nattr = 0, nmatch = 0, alloc_len;
	git_buf attrs = GIT_BUF_INIT;

	if (filter_def_scan_attrs(&attrs, &nattr, &nmatch, filter->attributes) < 0)
		return -1;

	GIT_ERROR_CHECK_ALLOC_MULTIPLY(&alloc_len, nattr, 2);
	GIT_ERROR_CHECK_ALLOC_MULTIPLY(&alloc_len, alloc_len, sizeof(char *));
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, sizeof(git_filter_def));

	fdef = git__calloc(1, alloc_len);
	GIT_ERROR_CHECK_ALLOC(fdef);

	fdef->filter_name = git__strdup(name);
	GIT_ERROR_CHECK_ALLOC(fdef->filter_name);

	fdef->filter      = filter;
	fdef->priority    = priority;
	fdef->nattrs      = nattr;
	fdef->nmatches    = nmatch;
	fdef->attrdata    = git_buf_detach(&attrs);

	filter_def_set_attrs(fdef);

	if (git_vector_insert(&filter_registry.filters, fdef) < 0) {
		git__free(fdef->filter_name);
		git__free(fdef->attrdata);
		git__free(fdef);
		return -1;
	}

	git_vector_sort(&filter_registry.filters);
	return 0;
}