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
typedef  scalar_t__ u_int32_t ;
struct ssh_identitylist {size_t nkeys; char** comments; int /*<<< orphan*/ * keys; } ;

/* Variables and functions */
 int SSH_ERR_AGENT_NO_IDENTITIES ; 
 int /*<<< orphan*/  SSH_FP_DEFAULT ; 
 int /*<<< orphan*/  fingerprint_hash ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* ssh_err (int) ; 
 int ssh_fetch_identitylist (int,struct ssh_identitylist**) ; 
 int /*<<< orphan*/  ssh_free_identitylist (struct ssh_identitylist*) ; 
 char* sshkey_fingerprint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sshkey_signatures_left (int /*<<< orphan*/ ) ; 
 int sshkey_size (int /*<<< orphan*/ ) ; 
 char* sshkey_type (int /*<<< orphan*/ ) ; 
 int sshkey_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
list_identities(int agent_fd, int do_fp)
{
	char *fp;
	int r;
	struct ssh_identitylist *idlist;
	u_int32_t left;
	size_t i;

	if ((r = ssh_fetch_identitylist(agent_fd, &idlist)) != 0) {
		if (r != SSH_ERR_AGENT_NO_IDENTITIES)
			fprintf(stderr, "error fetching identities: %s\n",
			    ssh_err(r));
		else
			printf("The agent has no identities.\n");
		return -1;
	}
	for (i = 0; i < idlist->nkeys; i++) {
		if (do_fp) {
			fp = sshkey_fingerprint(idlist->keys[i],
			    fingerprint_hash, SSH_FP_DEFAULT);
			printf("%u %s %s (%s)\n", sshkey_size(idlist->keys[i]),
			    fp == NULL ? "(null)" : fp, idlist->comments[i],
			    sshkey_type(idlist->keys[i]));
			free(fp);
		} else {
			if ((r = sshkey_write(idlist->keys[i], stdout)) != 0) {
				fprintf(stderr, "sshkey_write: %s\n",
				    ssh_err(r));
				continue;
			}
			fprintf(stdout, " %s", idlist->comments[i]);
			left = sshkey_signatures_left(idlist->keys[i]);
			if (left > 0)
				fprintf(stdout,
				    " [signatures left %d]", left);
			fprintf(stdout, "\n");
		}
	}
	ssh_free_identitylist(idlist);
	return 0;
}