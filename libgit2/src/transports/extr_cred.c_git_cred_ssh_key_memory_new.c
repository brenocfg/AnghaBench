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
 int /*<<< orphan*/  GIT_CREDTYPE_SSH_MEMORY ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int git_cred_ssh_key_type_new (int /*<<< orphan*/ **,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_cred_ssh_key_memory_new(
	git_cred **cred,
	const char *username,
	const char *publickey,
	const char *privatekey,
	const char *passphrase)
{
#ifdef GIT_SSH_MEMORY_CREDENTIALS
	return git_cred_ssh_key_type_new(
		cred,
		username,
		publickey,
		privatekey,
		passphrase,
		GIT_CREDTYPE_SSH_MEMORY);
#else
	GIT_UNUSED(cred);
	GIT_UNUSED(username);
	GIT_UNUSED(publickey);
	GIT_UNUSED(privatekey);
	GIT_UNUSED(passphrase);

	git_error_set(GIT_ERROR_INVALID,
		"this version of libgit2 was not built with ssh memory credentials.");
	return -1;
#endif
}