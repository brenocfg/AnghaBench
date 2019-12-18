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
struct pam_ssh_key {char* comment; struct sshkey* key; } ;
typedef  int /*<<< orphan*/  fn ;

/* Variables and functions */
 int /*<<< orphan*/  PAM_LOG_DEBUG ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  free (char*) ; 
 struct pam_ssh_key* malloc (int) ; 
 int /*<<< orphan*/  openpam_log (int /*<<< orphan*/ ,char*,char*,...) ; 
 int snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_private (char*,char const*,struct sshkey**,char**) ; 

__attribute__((used)) static struct pam_ssh_key *
pam_ssh_load_key(const char *dir, const char *kfn, const char *passphrase,
    int nullok)
{
	char fn[PATH_MAX];
	struct pam_ssh_key *psk;
	struct sshkey *key;
	char *comment;
	int ret;

	if (snprintf(fn, sizeof(fn), "%s/%s", dir, kfn) > (int)sizeof(fn))
		return (NULL);
	/*
	 * If the key is unencrypted, OpenSSL ignores the passphrase, so
	 * it will seem like the user typed in the right one.  This allows
	 * a user to circumvent nullok by providing a dummy passphrase.
	 * Verify that the key really *is* encrypted by trying to load it
	 * with an empty passphrase, and if the key is not encrypted,
	 * accept only an empty passphrase.
	 */
	ret = sshkey_load_private(fn, "", &key, &comment);
	if (ret == 0 && !(*passphrase == '\0' && nullok)) {
		sshkey_free(key);
		return (NULL);
	}
	if (ret != 0)
		ret = sshkey_load_private(fn, passphrase, &key, &comment);
	if (ret != 0) {
		openpam_log(PAM_LOG_DEBUG, "failed to load key from %s", fn);
		return (NULL);
	}

	openpam_log(PAM_LOG_DEBUG, "loaded '%s' from %s", comment, fn);
	if ((psk = malloc(sizeof(*psk))) == NULL) {
		sshkey_free(key);
		free(comment);
		return (NULL);
	}
	psk->key = key;
	psk->comment = comment;
	return (psk);
}