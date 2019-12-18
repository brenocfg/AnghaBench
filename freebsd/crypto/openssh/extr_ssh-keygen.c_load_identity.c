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
struct sshkey {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP_ALLOW_STDIN ; 
 int SSH_ERR_KEY_WRONG_PASSPHRASE ; 
 int /*<<< orphan*/  explicit_bzero (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ identity_passphrase ; 
 char* read_passphrase (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int sshkey_load_private (char*,char*,struct sshkey**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* xstrdup (scalar_t__) ; 

__attribute__((used)) static struct sshkey *
load_identity(char *filename)
{
	char *pass;
	struct sshkey *prv;
	int r;

	if ((r = sshkey_load_private(filename, "", &prv, NULL)) == 0)
		return prv;
	if (r != SSH_ERR_KEY_WRONG_PASSPHRASE)
		fatal("Load key \"%s\": %s", filename, ssh_err(r));
	if (identity_passphrase)
		pass = xstrdup(identity_passphrase);
	else
		pass = read_passphrase("Enter passphrase: ", RP_ALLOW_STDIN);
	r = sshkey_load_private(filename, pass, &prv, NULL);
	explicit_bzero(pass, strlen(pass));
	free(pass);
	if (r != 0)
		fatal("Load key \"%s\": %s", filename, ssh_err(r));
	return prv;
}