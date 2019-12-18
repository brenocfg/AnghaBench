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
struct t_pw {int /*<<< orphan*/  pebuf; } ;
struct t_confent {int dummy; } ;
typedef  int /*<<< orphan*/  passphrase1 ;
typedef  int /*<<< orphan*/  passphrase ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ Configindex ; 
 int /*<<< orphan*/  Passfile ; 
 int /*<<< orphan*/  creat (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct t_confent* gettcid (scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ t_changepw (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ t_getpass (char*,int,char*) ; 
 scalar_t__ t_getprecount () ; 
 int /*<<< orphan*/  t_makepwent (struct t_pw*,char*,char*,int /*<<< orphan*/ *,struct t_confent*) ; 

void doit(char *name)
{
	char passphrase[128], passphrase1[128];
	FILE *f;
	struct t_confent *tcent;
	struct t_pw eps_passwd;

	/* Get the config entry. */

	if (Configindex <= 0) {
		Configindex = t_getprecount();
	}
	tcent = gettcid(Configindex);
	if (tcent == NULL) {
		fprintf(stderr, "Invalid configuration file entry.\n");
		exit(1);
	}

	/* Ask for the passphrase twice. */

	printf("Setting passphrase for %s\n", name);

	if (t_getpass(passphrase, sizeof(passphrase), "Enter passphrase: ") < 0) {
		exit(1);
	}
	if (t_getpass(passphrase1, sizeof(passphrase1), "Verify: ") < 0) {
		exit(1);
	}
	if (strcmp(passphrase, passphrase1) != 0) {
		fprintf(stderr, "mismatch\n");
		exit(1);
	}

	/* Create the passphrase verifier. */

	t_makepwent(&eps_passwd, name, passphrase, NULL, tcent);

	/* Don't need these anymore. */

	memset(passphrase, 0, sizeof(passphrase));
	memset(passphrase1, 0, sizeof(passphrase1));

	/* See if the passphrase file is there; create it if not. */

	if ((f = fopen(Passfile, "r+")) == NULL) {
		creat(Passfile, 0400);
	} else {
		fclose(f);
	}

	/* Change the passphrase. */

	if (t_changepw(Passfile, &eps_passwd.pebuf) < 0) {
		fprintf(stderr, "Error changing passphrase\n");
		exit(1);
	}
}