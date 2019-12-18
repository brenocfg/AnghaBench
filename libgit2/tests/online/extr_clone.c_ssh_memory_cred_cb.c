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
typedef  int /*<<< orphan*/  git_cred ;

/* Variables and functions */
 unsigned int GIT_CREDTYPE_SSH_KEY ; 
 unsigned int GIT_CREDTYPE_USERNAME ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  _remote_ssh_passphrase ; 
 int /*<<< orphan*/  _remote_ssh_privkey ; 
 int /*<<< orphan*/  _remote_ssh_pubkey ; 
 int /*<<< orphan*/  _remote_user ; 
 int /*<<< orphan*/  free (char*) ; 
 int git_cred_ssh_key_memory_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int git_cred_username_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 char* read_key_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssh_memory_cred_cb(git_cred **cred, const char *url, const char *user_from_url,
		   unsigned int allowed_types, void *payload)
{
	GIT_UNUSED(url); GIT_UNUSED(user_from_url); GIT_UNUSED(payload);

	if (allowed_types & GIT_CREDTYPE_USERNAME)
		return git_cred_username_new(cred, _remote_user);

	if (allowed_types & GIT_CREDTYPE_SSH_KEY)
	{
		char *pubkey = read_key_file(_remote_ssh_pubkey);
		char *privkey = read_key_file(_remote_ssh_privkey);

		int ret = git_cred_ssh_key_memory_new(cred, _remote_user, pubkey, privkey, _remote_ssh_passphrase);

		if (privkey)
			free(privkey);
		if (pubkey)
			free(pubkey);
		return ret;
	}

	git_error_set(GIT_ERROR_NET, "unexpected cred type");
	return -1;
}