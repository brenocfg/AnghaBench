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
struct pubkey {struct pubkey* sig; int /*<<< orphan*/  siglen; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUBKEY ; 
 scalar_t__ config_string (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct pubkey*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 struct pubkey* read_pubkey (int) ; 
 int rsa_verify_cert (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pubkey*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static bool
verify_pubsignature(int fd_pkg, int fd_sig)
{
	struct pubkey *pk;
	const char *pubkey;
	bool ret;

	pk = NULL;
	pubkey = NULL;
	ret = false;
	if (config_string(PUBKEY, &pubkey) != 0) {
		warnx("No CONFIG_PUBKEY defined");
		goto cleanup;
	}

	if ((pk = read_pubkey(fd_sig)) == NULL) {
		warnx("Error reading signature");
		goto cleanup;
	}

	/* Verify the signature. */
	printf("Verifying signature with public key %s... ", pubkey);
	if (rsa_verify_cert(fd_pkg, pubkey, NULL, 0, pk->sig,
	    pk->siglen) == false) {
		fprintf(stderr, "Signature is not valid\n");
		goto cleanup;
	}

	ret = true;

cleanup:
	if (pk) {
		free(pk->sig);
		free(pk);
	}

	return (ret);
}