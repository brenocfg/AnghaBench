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
struct stat {int dummy; } ;
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;
struct ssh_krl {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__ atomicio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * ca_key_path ; 
 scalar_t__ cert_serial ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * identity_comment ; 
 char* identity_file ; 
 int /*<<< orphan*/  load_krl (char*,struct ssh_krl**) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int /*<<< orphan*/  ssh_krl_free (struct ssh_krl*) ; 
 struct ssh_krl* ssh_krl_init () ; 
 int /*<<< orphan*/  ssh_krl_set_comment (struct ssh_krl*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssh_krl_set_version (struct ssh_krl*,scalar_t__) ; 
 scalar_t__ ssh_krl_to_blob (struct ssh_krl*,struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_mutable_ptr (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_public (char*,struct sshkey**,int /*<<< orphan*/ *) ; 
 int stat (char*,struct stat*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 char* tilde_expand_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_krl_from_file (struct passwd*,char*,int,struct sshkey*,struct ssh_krl*) ; 
 int /*<<< orphan*/  vwrite ; 

__attribute__((used)) static void
do_gen_krl(struct passwd *pw, int updating, int argc, char **argv)
{
	struct ssh_krl *krl;
	struct stat sb;
	struct sshkey *ca = NULL;
	int fd, i, r, wild_ca = 0;
	char *tmp;
	struct sshbuf *kbuf;

	if (*identity_file == '\0')
		fatal("KRL generation requires an output file");
	if (stat(identity_file, &sb) == -1) {
		if (errno != ENOENT)
			fatal("Cannot access KRL \"%s\": %s",
			    identity_file, strerror(errno));
		if (updating)
			fatal("KRL \"%s\" does not exist", identity_file);
	}
	if (ca_key_path != NULL) {
		if (strcasecmp(ca_key_path, "none") == 0)
			wild_ca = 1;
		else {
			tmp = tilde_expand_filename(ca_key_path, pw->pw_uid);
			if ((r = sshkey_load_public(tmp, &ca, NULL)) != 0)
				fatal("Cannot load CA public key %s: %s",
				    tmp, ssh_err(r));
			free(tmp);
		}
	}

	if (updating)
		load_krl(identity_file, &krl);
	else if ((krl = ssh_krl_init()) == NULL)
		fatal("couldn't create KRL");

	if (cert_serial != 0)
		ssh_krl_set_version(krl, cert_serial);
	if (identity_comment != NULL)
		ssh_krl_set_comment(krl, identity_comment);

	for (i = 0; i < argc; i++)
		update_krl_from_file(pw, argv[i], wild_ca, ca, krl);

	if ((kbuf = sshbuf_new()) == NULL)
		fatal("sshbuf_new failed");
	if (ssh_krl_to_blob(krl, kbuf, NULL, 0) != 0)
		fatal("Couldn't generate KRL");
	if ((fd = open(identity_file, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1)
		fatal("open %s: %s", identity_file, strerror(errno));
	if (atomicio(vwrite, fd, sshbuf_mutable_ptr(kbuf), sshbuf_len(kbuf)) !=
	    sshbuf_len(kbuf))
		fatal("write %s: %s", identity_file, strerror(errno));
	close(fd);
	sshbuf_free(kbuf);
	ssh_krl_free(krl);
	sshkey_free(ca);
}