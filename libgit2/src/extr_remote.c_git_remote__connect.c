#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int (* git_transport_cb ) (TYPE_1__**,TYPE_2__*,void*) ;
struct TYPE_26__ {int (* connect ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,TYPE_5__ const*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* free ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ git_transport ;
struct TYPE_28__ {TYPE_5__ const* proxy; int /*<<< orphan*/  custom_headers; } ;
typedef  TYPE_4__ git_remote_connection_opts ;
struct TYPE_29__ {int (* transport ) (TYPE_1__**,TYPE_2__*,void*) ;void* payload; int /*<<< orphan*/ * credentials; } ;
typedef  TYPE_5__ git_remote_callbacks ;
struct TYPE_27__ {TYPE_1__* transport; } ;
typedef  TYPE_2__ git_remote ;
typedef  int /*<<< orphan*/  git_direction ;
typedef  int /*<<< orphan*/ * git_cred_acquire_cb ;
struct TYPE_30__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_7__ git_buf ;

/* Variables and functions */
 TYPE_7__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (TYPE_5__ const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_PROXY_OPTIONS_VERSION ; 
 int /*<<< orphan*/  GIT_REMOTE_CALLBACKS_VERSION ; 
 int GIT_TRANSPORTFLAGS_NONE ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_7__*) ; 
 int git_remote__urlfordirection (TYPE_7__*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__ const*) ; 
 int git_transport_new (TYPE_1__**,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int set_transport_callbacks (TYPE_1__*,TYPE_5__ const*) ; 
 int set_transport_custom_headers (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,TYPE_5__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

int git_remote__connect(git_remote *remote, git_direction direction, const git_remote_callbacks *callbacks, const git_remote_connection_opts *conn)
{
	git_transport *t;
	git_buf url = GIT_BUF_INIT;
	int flags = GIT_TRANSPORTFLAGS_NONE;
	int error;
	void *payload = NULL;
	git_cred_acquire_cb credentials = NULL;
	git_transport_cb transport = NULL;

	assert(remote);

	if (callbacks) {
		GIT_ERROR_CHECK_VERSION(callbacks, GIT_REMOTE_CALLBACKS_VERSION, "git_remote_callbacks");
		credentials = callbacks->credentials;
		transport   = callbacks->transport;
		payload     = callbacks->payload;
	}

	if (conn->proxy)
		GIT_ERROR_CHECK_VERSION(conn->proxy, GIT_PROXY_OPTIONS_VERSION, "git_proxy_options");

	t = remote->transport;

	if ((error = git_remote__urlfordirection(&url, remote, direction, callbacks)) < 0)
		goto on_error;

	/* If we don't have a transport object yet, and the caller specified a
	 * custom transport factory, use that */
	if (!t && transport &&
		(error = transport(&t, remote, payload)) < 0)
		goto on_error;

	/* If we still don't have a transport, then use the global
	 * transport registrations which map URI schemes to transport factories */
	if (!t && (error = git_transport_new(&t, remote, url.ptr)) < 0)
		goto on_error;

	if ((error = set_transport_custom_headers(t, conn->custom_headers)) != 0)
		goto on_error;

	if ((error = set_transport_callbacks(t, callbacks)) < 0 ||
	    (error = t->connect(t, url.ptr, credentials, payload, conn->proxy, direction, flags)) != 0)
		goto on_error;

	remote->transport = t;

	git_buf_dispose(&url);

	return 0;

on_error:
	if (t)
		t->free(t);

	git_buf_dispose(&url);

	if (t == remote->transport)
		remote->transport = NULL;

	return error;
}