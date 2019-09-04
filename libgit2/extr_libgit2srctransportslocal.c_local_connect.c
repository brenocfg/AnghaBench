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
struct TYPE_3__ {int connected; int direction; int flags; int /*<<< orphan*/ * repo; int /*<<< orphan*/  url; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ transport_local ;
typedef  int /*<<< orphan*/  git_transport ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  void git_proxy_options ;
typedef  void const* git_cred_acquire_cb ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_UNUSED (void const*) ; 
 int /*<<< orphan*/  free_heads (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__strdup (char const*) ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_path_from_url_or_path (int /*<<< orphan*/ *,char const*) ; 
 int git_repository_open (int /*<<< orphan*/ **,char const*) ; 
 scalar_t__ store_refs (TYPE_1__*) ; 

__attribute__((used)) static int local_connect(
	git_transport *transport,
	const char *url,
	git_cred_acquire_cb cred_acquire_cb,
	void *cred_acquire_payload,
	const git_proxy_options *proxy,
	int direction, int flags)
{
	git_repository *repo;
	int error;
	transport_local *t = (transport_local *) transport;
	const char *path;
	git_buf buf = GIT_BUF_INIT;

	GIT_UNUSED(cred_acquire_cb);
	GIT_UNUSED(cred_acquire_payload);
	GIT_UNUSED(proxy);

	if (t->connected)
		return 0;

	free_heads(&t->refs);

	t->url = git__strdup(url);
	GIT_ERROR_CHECK_ALLOC(t->url);
	t->direction = direction;
	t->flags = flags;

	/* 'url' may be a url or path; convert to a path */
	if ((error = git_path_from_url_or_path(&buf, url)) < 0) {
		git_buf_dispose(&buf);
		return error;
	}
	path = git_buf_cstr(&buf);

	error = git_repository_open(&repo, path);

	git_buf_dispose(&buf);

	if (error < 0)
		return -1;

	t->repo = repo;

	if (store_refs(t) < 0)
		return -1;

	t->connected = 1;

	return 0;
}