#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {char const* name; int /*<<< orphan*/ * repository; } ;
typedef  TYPE_1__ git_remote_create_options ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ERROR ; 
 TYPE_1__ GIT_REMOTE_CREATE_OPTIONS_INIT ; 
 scalar_t__ canonicalize_url (int /*<<< orphan*/ *,char const*) ; 
 int ensure_remote_name_is_valid (char const*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_remote_create_with_opts (int /*<<< orphan*/ **,char const*,TYPE_1__*) ; 

int git_remote_create(git_remote **out, git_repository *repo, const char *name, const char *url)
{
	git_buf buf = GIT_BUF_INIT;
	int error;
	git_remote_create_options opts = GIT_REMOTE_CREATE_OPTIONS_INIT;

	/* Those 2 tests are duplicated here because of backward-compatibility */
	if ((error = ensure_remote_name_is_valid(name)) < 0)
		return error;

	if (canonicalize_url(&buf, url) < 0)
		return GIT_ERROR;

	git_buf_clear(&buf);

	opts.repository = repo;
	opts.name = name;

	error = git_remote_create_with_opts(out, url, &opts);

	git_buf_dispose(&buf);

	return error;
}