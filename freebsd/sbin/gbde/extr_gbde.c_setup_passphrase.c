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
struct g_bde_softc {int /*<<< orphan*/  sha2; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int RPP_ECHO_OFF ; 
 int RPP_REQUIRE_TTY ; 
 int SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  g_bde_hash_pass (struct g_bde_softc*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int read (int,char*,int) ; 
 char* readpassphrase (char*,char*,int,int) ; 
 char* sha2 ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
setup_passphrase(struct g_bde_softc *sc, int sure, const char *input,
    const char *keyfile)
{
	char buf1[BUFSIZ + SHA512_DIGEST_LENGTH];
	char buf2[BUFSIZ + SHA512_DIGEST_LENGTH];
	char *p;
	int kfd, klen, bpos = 0;

	if (keyfile != NULL) {
		/* Read up to BUFSIZ bytes from keyfile */
		kfd = open(keyfile, O_RDONLY, 0);
		if (kfd < 0)
			err(1, "%s", keyfile);
		klen = read(kfd, buf1, BUFSIZ);
		if (klen == -1)
			err(1, "%s", keyfile);
		close(kfd);

		/* Prepend the passphrase with the hash of the key read */
		g_bde_hash_pass(sc, buf1, klen);
		memcpy(buf1, sc->sha2, SHA512_DIGEST_LENGTH);
		memcpy(buf2, sc->sha2, SHA512_DIGEST_LENGTH);
		bpos = SHA512_DIGEST_LENGTH;
	}

	if (input != NULL) {
		if (strlen(input) >= BUFSIZ)
			errx(1, "Passphrase too long");
		strcpy(buf1 + bpos, input);

		g_bde_hash_pass(sc, buf1, strlen(buf1 + bpos) + bpos);
		memcpy(sha2, sc->sha2, SHA512_DIGEST_LENGTH);
		return;
	}
	for (;;) {
		p = readpassphrase(
		    sure ? "Enter new passphrase:" : "Enter passphrase: ",
		    buf1 + bpos, sizeof buf1 - bpos,
		    RPP_ECHO_OFF | RPP_REQUIRE_TTY);
		if (p == NULL)
			err(1, "readpassphrase");

		if (sure) {
			p = readpassphrase("Reenter new passphrase: ",
			    buf2 + bpos, sizeof buf2 - bpos,
			    RPP_ECHO_OFF | RPP_REQUIRE_TTY);
			if (p == NULL)
				err(1, "readpassphrase");

			if (strcmp(buf1 + bpos, buf2 + bpos)) {
				printf("They didn't match.\n");
				continue;
			}
		}
		if (strlen(buf1 + bpos) < 3) {
			printf("Too short passphrase.\n");
			continue;
		}
		break;
	}
	g_bde_hash_pass(sc, buf1, strlen(buf1 + bpos) + bpos);
	memcpy(sha2, sc->sha2, SHA512_DIGEST_LENGTH);
}