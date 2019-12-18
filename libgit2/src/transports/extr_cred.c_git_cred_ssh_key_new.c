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
 int /*<<< orphan*/  GIT_CREDTYPE_SSH_KEY ; 
 int git_cred_ssh_key_type_new (int /*<<< orphan*/ **,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ) ; 

int git_cred_ssh_key_new(
	git_cred **cred,
	const char *username,
	const char *publickey,
	const char *privatekey,
	const char *passphrase)
{
	return git_cred_ssh_key_type_new(
		cred,
		username,
		publickey,
		privatekey,
		passphrase,
		GIT_CREDTYPE_SSH_KEY);
}