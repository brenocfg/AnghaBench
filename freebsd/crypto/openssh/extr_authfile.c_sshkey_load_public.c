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
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 struct sshkey* sshkey_new (int /*<<< orphan*/ ) ; 
 int sshkey_try_load_public (struct sshkey*,char const*,char**) ; 

int
sshkey_load_public(const char *filename, struct sshkey **keyp, char **commentp)
{
	struct sshkey *pub = NULL;
	char *file = NULL;
	int r;

	if (keyp != NULL)
		*keyp = NULL;
	if (commentp != NULL)
		*commentp = NULL;

	if ((pub = sshkey_new(KEY_UNSPEC)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshkey_try_load_public(pub, filename, commentp)) == 0) {
		if (keyp != NULL) {
			*keyp = pub;
			pub = NULL;
		}
		r = 0;
		goto out;
	}
	sshkey_free(pub);

	/* try .pub suffix */
	if (asprintf(&file, "%s.pub", filename) == -1)
		return SSH_ERR_ALLOC_FAIL;
	if ((pub = sshkey_new(KEY_UNSPEC)) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if ((r = sshkey_try_load_public(pub, file, commentp)) == 0) {
		if (keyp != NULL) {
			*keyp = pub;
			pub = NULL;
		}
		r = 0;
	}
 out:
	free(file);
	sshkey_free(pub);
	return r;
}