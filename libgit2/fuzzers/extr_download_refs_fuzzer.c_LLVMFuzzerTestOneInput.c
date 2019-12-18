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
struct fuzzer_buffer {unsigned char const* member_0; size_t member_1; } ;
struct TYPE_4__ {struct fuzzer_buffer* payload; int /*<<< orphan*/  transport; } ;
typedef  TYPE_1__ git_remote_callbacks ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 TYPE_1__ GIT_REMOTE_CALLBACKS_INIT ; 
 int /*<<< orphan*/  fuzzer_git_abort (char*) ; 
 int /*<<< orphan*/  fuzzer_transport_cb ; 
 scalar_t__ git_remote_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_remote_create_anonymous (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_download (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

int LLVMFuzzerTestOneInput(const unsigned char *data, size_t size)
{
	struct fuzzer_buffer buffer = { data, size };
	git_remote_callbacks callbacks = GIT_REMOTE_CALLBACKS_INIT;
	git_remote *remote;

	if (git_remote_create_anonymous(&remote, repo, "fuzzer://remote-url") < 0)
		fuzzer_git_abort("git_remote_create");

	callbacks.transport = fuzzer_transport_cb;
	callbacks.payload = &buffer;

	if (git_remote_connect(remote, GIT_DIRECTION_FETCH,
	    &callbacks, NULL, NULL) < 0)
		goto out;

	git_remote_download(remote, NULL, NULL);

    out:
	git_remote_free(remote);

	return 0;
}