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
 scalar_t__ ENOENT ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  fatal (char*,char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* ssh_err (int) ; 
 int ssh_remove_identity (int,struct sshkey*) ; 
 int /*<<< orphan*/  sshkey_equal_public (struct sshkey*,struct sshkey*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_public (char const*,struct sshkey**,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*) ; 

__attribute__((used)) static int
delete_file(int agent_fd, const char *filename, int key_only, int qflag)
{
	struct sshkey *public, *cert = NULL;
	char *certpath = NULL, *comment = NULL;
	int r, ret = -1;

	if ((r = sshkey_load_public(filename, &public,  &comment)) != 0) {
		printf("Bad key file %s: %s\n", filename, ssh_err(r));
		return -1;
	}
	if ((r = ssh_remove_identity(agent_fd, public)) == 0) {
		if (!qflag) {
			fprintf(stderr, "Identity removed: %s (%s)\n",
			    filename, comment);
		}
		ret = 0;
	} else
		fprintf(stderr, "Could not remove identity \"%s\": %s\n",
		    filename, ssh_err(r));

	if (key_only)
		goto out;

	/* Now try to delete the corresponding certificate too */
	free(comment);
	comment = NULL;
	xasprintf(&certpath, "%s-cert.pub", filename);
	if ((r = sshkey_load_public(certpath, &cert, &comment)) != 0) {
		if (r != SSH_ERR_SYSTEM_ERROR || errno != ENOENT)
			error("Failed to load certificate \"%s\": %s",
			    certpath, ssh_err(r));
		goto out;
	}

	if (!sshkey_equal_public(cert, public))
		fatal("Certificate %s does not match private key %s",
		    certpath, filename);

	if ((r = ssh_remove_identity(agent_fd, cert)) == 0) {
		if (!qflag) {
			fprintf(stderr, "Identity removed: %s (%s)\n",
			    certpath, comment);
		}
		ret = 0;
	} else
		fprintf(stderr, "Could not remove identity \"%s\": %s\n",
		    certpath, ssh_err(r));

 out:
	sshkey_free(cert);
	sshkey_free(public);
	free(certpath);
	free(comment);

	return ret;
}