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
#define  KEY_DSA 133 
#define  KEY_ECDSA 132 
#define  KEY_ED25519 131 
#define  KEY_RSA 130 
#define  KEY_UNSPEC 129 
#define  KEY_XMSS 128 
 int SSH_ERR_KEY_CERT_MISMATCH ; 
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 int sshkey_cert_copy (struct sshkey*,struct sshkey*) ; 
 scalar_t__ sshkey_equal_public (struct sshkey*,struct sshkey*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_load_cert (char const*,struct sshkey**) ; 
 int sshkey_load_private_type (int,char const*,char const*,struct sshkey**,int /*<<< orphan*/ *,int*) ; 
 int sshkey_to_certified (struct sshkey*) ; 

int
sshkey_load_private_cert(int type, const char *filename, const char *passphrase,
    struct sshkey **keyp, int *perm_ok)
{
	struct sshkey *key = NULL, *cert = NULL;
	int r;

	if (keyp != NULL)
		*keyp = NULL;

	switch (type) {
#ifdef WITH_OPENSSL
	case KEY_RSA:
	case KEY_DSA:
	case KEY_ECDSA:
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
	case KEY_XMSS:
	case KEY_UNSPEC:
		break;
	default:
		return SSH_ERR_KEY_TYPE_UNKNOWN;
	}

	if ((r = sshkey_load_private_type(type, filename,
	    passphrase, &key, NULL, perm_ok)) != 0 ||
	    (r = sshkey_load_cert(filename, &cert)) != 0)
		goto out;

	/* Make sure the private key matches the certificate */
	if (sshkey_equal_public(key, cert) == 0) {
		r = SSH_ERR_KEY_CERT_MISMATCH;
		goto out;
	}

	if ((r = sshkey_to_certified(key)) != 0 ||
	    (r = sshkey_cert_copy(cert, key)) != 0)
		goto out;
	r = 0;
	if (keyp != NULL) {
		*keyp = key;
		key = NULL;
	}
 out:
	sshkey_free(key);
	sshkey_free(cert);
	return r;
}