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
 int /*<<< orphan*/  KEY_UNSPEC ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 struct sshkey* sshkey_new (int /*<<< orphan*/ ) ; 
 int sshkey_try_load_public (struct sshkey*,char*,int /*<<< orphan*/ *) ; 

int
sshkey_load_cert(const char *filename, struct sshkey **keyp)
{
	struct sshkey *pub = NULL;
	char *file = NULL;
	int r = SSH_ERR_INTERNAL_ERROR;

	if (keyp != NULL)
		*keyp = NULL;

	if (asprintf(&file, "%s-cert.pub", filename) == -1)
		return SSH_ERR_ALLOC_FAIL;

	if ((pub = sshkey_new(KEY_UNSPEC)) == NULL) {
		goto out;
	}
	if ((r = sshkey_try_load_public(pub, file, NULL)) != 0)
		goto out;
	/* success */
	if (keyp != NULL) {
		*keyp = pub;
		pub = NULL;
	}
	r = 0;
 out:
	free(file);
	sshkey_free(pub);
	return r;
}