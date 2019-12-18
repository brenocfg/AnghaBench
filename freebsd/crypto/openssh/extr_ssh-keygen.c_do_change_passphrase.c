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
 int /*<<< orphan*/  RP_ALLOW_STDIN ; 
 int SSH_ERR_KEY_WRONG_PASSPHRASE ; 
 int /*<<< orphan*/  ask_filename (struct passwd*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  explicit_bzero (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  have_identity ; 
 int /*<<< orphan*/  identity_file ; 
 scalar_t__ identity_new_passphrase ; 
 scalar_t__ identity_passphrase ; 
 int /*<<< orphan*/  mprintf (char*,char*) ; 
 int /*<<< orphan*/  new_format_cipher ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* read_passphrase (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rounds ; 
 char* ssh_err (int) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_private (int /*<<< orphan*/ ,char*,struct sshkey**,char**) ; 
 int sshkey_save_private (struct sshkey*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  use_new_format ; 
 char* xstrdup (scalar_t__) ; 

__attribute__((used)) static void
do_change_passphrase(struct passwd *pw)
{
	char *comment;
	char *old_passphrase, *passphrase1, *passphrase2;
	struct stat st;
	struct sshkey *private;
	int r;

	if (!have_identity)
		ask_filename(pw, "Enter file in which the key is");
	if (stat(identity_file, &st) < 0)
		fatal("%s: %s", identity_file, strerror(errno));
	/* Try to load the file with empty passphrase. */
	r = sshkey_load_private(identity_file, "", &private, &comment);
	if (r == SSH_ERR_KEY_WRONG_PASSPHRASE) {
		if (identity_passphrase)
			old_passphrase = xstrdup(identity_passphrase);
		else
			old_passphrase =
			    read_passphrase("Enter old passphrase: ",
			    RP_ALLOW_STDIN);
		r = sshkey_load_private(identity_file, old_passphrase,
		    &private, &comment);
		explicit_bzero(old_passphrase, strlen(old_passphrase));
		free(old_passphrase);
		if (r != 0)
			goto badkey;
	} else if (r != 0) {
 badkey:
		fatal("Failed to load key %s: %s", identity_file, ssh_err(r));
	}
	if (comment)
		mprintf("Key has comment '%s'\n", comment);

	/* Ask the new passphrase (twice). */
	if (identity_new_passphrase) {
		passphrase1 = xstrdup(identity_new_passphrase);
		passphrase2 = NULL;
	} else {
		passphrase1 =
			read_passphrase("Enter new passphrase (empty for no "
			    "passphrase): ", RP_ALLOW_STDIN);
		passphrase2 = read_passphrase("Enter same passphrase again: ",
		    RP_ALLOW_STDIN);

		/* Verify that they are the same. */
		if (strcmp(passphrase1, passphrase2) != 0) {
			explicit_bzero(passphrase1, strlen(passphrase1));
			explicit_bzero(passphrase2, strlen(passphrase2));
			free(passphrase1);
			free(passphrase2);
			printf("Pass phrases do not match.  Try again.\n");
			exit(1);
		}
		/* Destroy the other copy. */
		explicit_bzero(passphrase2, strlen(passphrase2));
		free(passphrase2);
	}

	/* Save the file using the new passphrase. */
	if ((r = sshkey_save_private(private, identity_file, passphrase1,
	    comment, use_new_format, new_format_cipher, rounds)) != 0) {
		error("Saving key \"%s\" failed: %s.",
		    identity_file, ssh_err(r));
		explicit_bzero(passphrase1, strlen(passphrase1));
		free(passphrase1);
		sshkey_free(private);
		free(comment);
		exit(1);
	}
	/* Destroy the passphrase and the copy of the key in memory. */
	explicit_bzero(passphrase1, strlen(passphrase1));
	free(passphrase1);
	sshkey_free(private);		 /* Destroys contents */
	free(comment);

	printf("Your identification has been saved with the new passphrase.\n");
	exit(0);
}