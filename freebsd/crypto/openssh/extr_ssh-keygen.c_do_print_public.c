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
struct passwd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ask_filename (struct passwd*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  have_identity ; 
 int /*<<< orphan*/  identity_file ; 
 struct sshkey* load_identity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_write (struct sshkey*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_print_public(struct passwd *pw)
{
	struct sshkey *prv;
	struct stat st;
	int r;

	if (!have_identity)
		ask_filename(pw, "Enter file in which the key is");
	if (stat(identity_file, &st) < 0)
		fatal("%s: %s", identity_file, strerror(errno));
	prv = load_identity(identity_file);
	if ((r = sshkey_write(prv, stdout)) != 0)
		error("sshkey_write failed: %s", ssh_err(r));
	sshkey_free(prv);
	fprintf(stdout, "\n");
	exit(0);
}