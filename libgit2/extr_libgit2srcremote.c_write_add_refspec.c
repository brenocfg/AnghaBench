#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_7__ {scalar_t__ klass; } ;

/* Variables and functions */
 char* CONFIG_FETCH_FMT ; 
 char* CONFIG_PUSH_FMT ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_EINVALIDSPEC ; 
 scalar_t__ GIT_ERROR_NOMEMORY ; 
 int ensure_remote_name_is_valid (char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_printf (TYPE_1__*,char const*,char const*) ; 
 int git_config_set_multivar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_2__* git_error_last () ; 
 int /*<<< orphan*/  git_refspec__dispose (int /*<<< orphan*/ *) ; 
 int git_refspec__parse (int /*<<< orphan*/ *,char const*,int) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_add_refspec(git_repository *repo, const char *name, const char *refspec, bool fetch)
{
	git_config *cfg;
	git_buf var = GIT_BUF_INIT;
	git_refspec spec;
	const char *fmt;
	int error;

	if ((error = git_repository_config__weakptr(&cfg, repo)) < 0)
	    return error;

	fmt = fetch ? CONFIG_FETCH_FMT : CONFIG_PUSH_FMT;

	if ((error = ensure_remote_name_is_valid(name)) < 0)
		return error;

	if ((error = git_refspec__parse(&spec, refspec, fetch)) < 0) {
		if (git_error_last()->klass != GIT_ERROR_NOMEMORY)
			error = GIT_EINVALIDSPEC;

		return error;
	}

	git_refspec__dispose(&spec);

	if ((error = git_buf_printf(&var, fmt, name)) < 0)
		return error;

	/*
	 * "$^" is a unmatcheable regexp: it will not match anything at all, so
	 * all values will be considered new and we will not replace any
	 * present value.
	 */
	if ((error = git_config_set_multivar(cfg, var.ptr, "$^", refspec)) < 0) {
		goto cleanup;
	}

cleanup:
	git_buf_dispose(&var);
	return 0;
}