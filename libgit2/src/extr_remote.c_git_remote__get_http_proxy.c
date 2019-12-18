#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* name; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_remote ;
struct TYPE_8__ {scalar_t__ value; } ;
typedef  TYPE_2__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int git__getenv (int /*<<< orphan*/ *,char*) ; 
 char* git__strdup (scalar_t__) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int git_config__lookup_entry (TYPE_2__**,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_entry_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int git_remote__get_http_proxy(git_remote *remote, bool use_ssl, char **proxy_url)
{
	git_config *cfg;
	git_config_entry *ce = NULL;
	git_buf val = GIT_BUF_INIT;
	int error;

	assert(remote);

	if (!proxy_url || !remote->repo)
		return -1;

	*proxy_url = NULL;

	if ((error = git_repository_config__weakptr(&cfg, remote->repo)) < 0)
		return error;

	/* Go through the possible sources for proxy configuration, from most specific
	 * to least specific. */

	/* remote.<name>.proxy config setting */
	if (remote->name && remote->name[0]) {
		git_buf buf = GIT_BUF_INIT;

		if ((error = git_buf_printf(&buf, "remote.%s.proxy", remote->name)) < 0)
			return error;

		error = git_config__lookup_entry(&ce, cfg, git_buf_cstr(&buf), false);
		git_buf_dispose(&buf);

		if (error < 0)
			return error;

		if (ce && ce->value) {
			*proxy_url = git__strdup(ce->value);
			goto found;
		}
	}

	/* http.proxy config setting */
	if ((error = git_config__lookup_entry(&ce, cfg, "http.proxy", false)) < 0)
		return error;

	if (ce && ce->value) {
		*proxy_url = git__strdup(ce->value);
		goto found;
	}

	/* http_proxy / https_proxy environment variables */
	error = git__getenv(&val, use_ssl ? "https_proxy" : "http_proxy");

	/* try uppercase environment variables */
	if (error == GIT_ENOTFOUND)
		error = git__getenv(&val, use_ssl ? "HTTPS_PROXY" : "HTTP_PROXY");

	if (error < 0) {
		if (error == GIT_ENOTFOUND) {
			git_error_clear();
			error = 0;
		}

		return error;
	}

	*proxy_url = git_buf_detach(&val);

found:
	GIT_ERROR_CHECK_ALLOC(*proxy_url);
	git_config_entry_free(ce);

	return 0;
}