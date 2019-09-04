#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int (* git_remote_create_cb ) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char const*,void*) ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_3__ {int (* remote_cb ) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char const*,void*) ;void* remote_cb_payload; } ;
typedef  TYPE_1__ git_clone_options ;

/* Variables and functions */
 int GIT_PATH_MAX ; 
 int default_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char const*,void*) ; 
 scalar_t__ git_path_exists (char const*) ; 
 scalar_t__ git_path_isdir (char const*) ; 
 scalar_t__ git_path_root (char const*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p_realpath (char const*,char*) ; 

__attribute__((used)) static int create_and_configure_origin(
		git_remote **out,
		git_repository *repo,
		const char *url,
		const git_clone_options *options)
{
	int error;
	git_remote *origin = NULL;
	char buf[GIT_PATH_MAX];
	git_remote_create_cb remote_create = options->remote_cb;
	void *payload = options->remote_cb_payload;

	/* If the path exists and is a dir, the url should be the absolute path */
	if (git_path_root(url) < 0 && git_path_exists(url) && git_path_isdir(url)) {
		if (p_realpath(url, buf) == NULL)
			return -1;

		url = buf;
	}

	if (!remote_create) {
		remote_create = default_remote_create;
		payload = NULL;
	}

	if ((error = remote_create(&origin, repo, "origin", url, payload)) < 0)
		goto on_error;

	*out = origin;
	return 0;

on_error:
	git_remote_free(origin);
	return error;
}