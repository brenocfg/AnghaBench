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

/* Variables and functions */
 int /*<<< orphan*/  _record_cbs_data ; 
 int /*<<< orphan*/ * _remote ; 
 int /*<<< orphan*/  _remote_default ; 
 int /*<<< orphan*/  _remote_pass ; 
 int /*<<< orphan*/  _remote_ssh_key ; 
 int /*<<< orphan*/  _remote_ssh_passphrase ; 
 int /*<<< orphan*/  _remote_ssh_pubkey ; 
 int /*<<< orphan*/  _remote_url ; 
 int /*<<< orphan*/  _remote_user ; 
 int /*<<< orphan*/ * _repo ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_callbacks_data_clear (int /*<<< orphan*/ *) ; 

void test_online_push__cleanup(void)
{
	if (_remote)
		git_remote_free(_remote);
	_remote = NULL;

	git__free(_remote_url);
	git__free(_remote_user);
	git__free(_remote_pass);
	git__free(_remote_ssh_key);
	git__free(_remote_ssh_pubkey);
	git__free(_remote_ssh_passphrase);
	git__free(_remote_default);

	/* Freed by cl_git_sandbox_cleanup */
	_repo = NULL;

	record_callbacks_data_clear(&_record_cbs_data);

	cl_fixture_cleanup("testrepo.git");
	cl_git_sandbox_cleanup();
}