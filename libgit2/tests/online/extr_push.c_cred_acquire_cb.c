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
 unsigned int GIT_CREDTYPE_DEFAULT ; 
 unsigned int GIT_CREDTYPE_SSH_KEY ; 
 unsigned int GIT_CREDTYPE_USERNAME ; 
 unsigned int GIT_CREDTYPE_USERPASS_PLAINTEXT ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  _remote_default ; 
 int /*<<< orphan*/  _remote_pass ; 
 int /*<<< orphan*/  _remote_ssh_key ; 
 int /*<<< orphan*/  _remote_ssh_passphrase ; 
 int /*<<< orphan*/  _remote_ssh_pubkey ; 
 int /*<<< orphan*/  _remote_user ; 
 int git_cred_default_new (int /*<<< orphan*/ **) ; 
 int git_cred_ssh_key_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_cred_username_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_cred_userpass_plaintext_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int cred_acquire_cb(
	git_cred **cred,
	const char *url,
	const char *user_from_url,
	unsigned int allowed_types,
	void *payload)
{
	GIT_UNUSED(url);
	GIT_UNUSED(user_from_url);
	GIT_UNUSED(payload);

	if (GIT_CREDTYPE_USERNAME & allowed_types) {
		if (!_remote_user) {
			printf("GITTEST_REMOTE_USER must be set\n");
			return -1;
		}

		return git_cred_username_new(cred, _remote_user);
	}

	if (GIT_CREDTYPE_DEFAULT & allowed_types) {
		if (!_remote_default) {
			printf("GITTEST_REMOTE_DEFAULT must be set to use NTLM/Negotiate credentials\n");
			return -1;
		}

		return git_cred_default_new(cred);
	}

	if (GIT_CREDTYPE_SSH_KEY & allowed_types) {
		if (!_remote_user || !_remote_ssh_pubkey || !_remote_ssh_key || !_remote_ssh_passphrase) {
			printf("GITTEST_REMOTE_USER, GITTEST_REMOTE_SSH_PUBKEY, GITTEST_REMOTE_SSH_KEY and GITTEST_REMOTE_SSH_PASSPHRASE must be set\n");
			return -1;
		}

		return git_cred_ssh_key_new(cred, _remote_user, _remote_ssh_pubkey, _remote_ssh_key, _remote_ssh_passphrase);
	}

	if (GIT_CREDTYPE_USERPASS_PLAINTEXT & allowed_types) {
		if (!_remote_user || !_remote_pass) {
			printf("GITTEST_REMOTE_USER and GITTEST_REMOTE_PASS must be set\n");
			return -1;
		}

		return git_cred_userpass_plaintext_new(cred, _remote_user, _remote_pass);
	}

	return -1;
}