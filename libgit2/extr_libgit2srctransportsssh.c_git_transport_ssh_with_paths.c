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
typedef  int /*<<< orphan*/  git_transport ;
typedef  void git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_transport_ssh_with_paths(git_transport **out, git_remote *owner, void *payload)
{
#ifdef GIT_SSH
	git_strarray *paths = (git_strarray *) payload;
	git_transport *transport;
	transport_smart *smart;
	ssh_subtransport *t;
	int error;
	git_smart_subtransport_definition ssh_definition = {
		git_smart_subtransport_ssh,
		0, /* no RPC */
		NULL,
	};

	if (paths->count != 2) {
		git_error_set(GIT_ERROR_SSH, "invalid ssh paths, must be two strings");
		return GIT_EINVALIDSPEC;
	}

	if ((error = git_transport_smart(&transport, owner, &ssh_definition)) < 0)
		return error;

	smart = (transport_smart *) transport;
	t = (ssh_subtransport *) smart->wrapped;

	t->cmd_uploadpack = git__strdup(paths->strings[0]);
	GIT_ERROR_CHECK_ALLOC(t->cmd_uploadpack);
	t->cmd_receivepack = git__strdup(paths->strings[1]);
	GIT_ERROR_CHECK_ALLOC(t->cmd_receivepack);

	*out = transport;
	return 0;
#else
	GIT_UNUSED(owner);
	GIT_UNUSED(payload);

	assert(out);
	*out = NULL;

	git_error_set(GIT_ERROR_INVALID, "cannot create SSH transport. Library was built without SSH support");
	return -1;
#endif
}