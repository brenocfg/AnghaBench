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
 unsigned int GIT_CREDTYPE_USERPASS_PLAINTEXT ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int ask (char**,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int git_cred_ssh_key_new (int /*<<< orphan*/ **,char*,char*,char*,char*) ; 
 int git_cred_username_new (int /*<<< orphan*/ **,char*) ; 
 int git_cred_userpass_plaintext_new (int /*<<< orphan*/ **,char*,char*) ; 
 char* malloc (int) ; 
 int snprintf (char*,int,char*,char*) ; 
 char* strdup (char const*) ; 

int cred_acquire_cb(git_cred **out,
		const char *url,
		const char *username_from_url,
		unsigned int allowed_types,
		void *payload)
{
	char *username = NULL, *password = NULL, *privkey = NULL, *pubkey = NULL;
	int error = 1;

	UNUSED(url);
	UNUSED(payload);

	if (username_from_url) {
		if ((username = strdup(username_from_url)) == NULL)
			goto out;
	} else if ((error = ask(&username, "Username:", 0)) < 0) {
		goto out;
	}

	if (allowed_types & GIT_CREDTYPE_SSH_KEY) {
		int n;

		if ((error = ask(&privkey, "SSH Key:", 0)) < 0 ||
		    (error = ask(&password, "Password:", 1)) < 0)
			goto out;

		if ((n = snprintf(NULL, 0, "%s.pub", privkey)) < 0 ||
		    (pubkey = malloc(n + 1)) == NULL ||
		    (n = snprintf(pubkey, n + 1, "%s.pub", privkey)) < 0)
			goto out;

		error = git_cred_ssh_key_new(out, username, pubkey, privkey, password);
	} else if (allowed_types & GIT_CREDTYPE_USERPASS_PLAINTEXT) {
		if ((error = ask(&password, "Password:", 1)) < 0)
			goto out;

		error = git_cred_userpass_plaintext_new(out, username, password);
	} else if (allowed_types & GIT_CREDTYPE_USERNAME) {
		error = git_cred_username_new(out, username);
	}

out:
	free(username);
	free(password);
	free(privkey);
	free(pubkey);
	return error;
}