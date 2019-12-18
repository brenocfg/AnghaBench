#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct sshkey {TYPE_1__* cert; } const sshkey ;
struct TYPE_2__ {struct sshkey const* signature_key; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_UNSPEC ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_KEY_NOT_FOUND ; 
 int SSH_ERR_SYSTEM_ERROR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int sshkey_equal (struct sshkey const*,struct sshkey const*) ; 
 int sshkey_equal_public (struct sshkey const*,struct sshkey const*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey const*) ; 
 scalar_t__ sshkey_is_cert (struct sshkey const*) ; 
 struct sshkey const* sshkey_new (int /*<<< orphan*/ ) ; 
 int sshkey_read (struct sshkey const*,char**) ; 

int
sshkey_in_file(struct sshkey *key, const char *filename, int strict_type,
    int check_ca)
{
	FILE *f;
	char *line = NULL, *cp;
	size_t linesize = 0;
	int r = 0;
	struct sshkey *pub = NULL;

	int (*sshkey_compare)(const struct sshkey *, const struct sshkey *) =
	    strict_type ?  sshkey_equal : sshkey_equal_public;

	if ((f = fopen(filename, "r")) == NULL)
		return SSH_ERR_SYSTEM_ERROR;

	while (getline(&line, &linesize, f) != -1) {
		cp = line;

		/* Skip leading whitespace. */
		for (; *cp && (*cp == ' ' || *cp == '\t'); cp++)
			;

		/* Skip comments and empty lines */
		switch (*cp) {
		case '#':
		case '\n':
		case '\0':
			continue;
		}

		if ((pub = sshkey_new(KEY_UNSPEC)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if ((r = sshkey_read(pub, &cp)) != 0)
			goto out;
		if (sshkey_compare(key, pub) ||
		    (check_ca && sshkey_is_cert(key) &&
		    sshkey_compare(key->cert->signature_key, pub))) {
			r = 0;
			goto out;
		}
		sshkey_free(pub);
		pub = NULL;
	}
	r = SSH_ERR_KEY_NOT_FOUND;
 out:
	free(line);
	sshkey_free(pub);
	fclose(f);
	return r;
}