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
struct ssh_krl {int dummy; } ;
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* identity_file ; 
 int /*<<< orphan*/  load_krl (char*,struct ssh_krl**) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int ssh_krl_check_key (struct ssh_krl*,struct sshkey*) ; 
 int /*<<< orphan*/  ssh_krl_free (struct ssh_krl*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_public (char*,struct sshkey**,char**) ; 

__attribute__((used)) static void
do_check_krl(struct passwd *pw, int argc, char **argv)
{
	int i, r, ret = 0;
	char *comment;
	struct ssh_krl *krl;
	struct sshkey *k;

	if (*identity_file == '\0')
		fatal("KRL checking requires an input file");
	load_krl(identity_file, &krl);
	for (i = 0; i < argc; i++) {
		if ((r = sshkey_load_public(argv[i], &k, &comment)) != 0)
			fatal("Cannot load public key %s: %s",
			    argv[i], ssh_err(r));
		r = ssh_krl_check_key(krl, k);
		printf("%s%s%s%s: %s\n", argv[i],
		    *comment ? " (" : "", comment, *comment ? ")" : "",
		    r == 0 ? "ok" : "REVOKED");
		if (r != 0)
			ret = 1;
		sshkey_free(k);
		free(comment);
	}
	ssh_krl_free(krl);
	exit(ret);
}