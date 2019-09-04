#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int (* git_transport_cb ) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  git_transport ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  GIT_TRANSPORT_VERSION ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int transport_find_fn (int (*) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*),char const*,void**) ; 

int git_transport_new(git_transport **out, git_remote *owner, const char *url)
{
	git_transport_cb fn;
	git_transport *transport;
	void *param;
	int error;

	if ((error = transport_find_fn(&fn, url, &param)) == GIT_ENOTFOUND) {
		git_error_set(GIT_ERROR_NET, "unsupported URL protocol");
		return -1;
	} else if (error < 0)
		return error;

	if ((error = fn(&transport, owner, param)) < 0)
		return error;

	GIT_ERROR_CHECK_VERSION(transport, GIT_TRANSPORT_VERSION, "git_transport");

	*out = transport;

	return 0;
}