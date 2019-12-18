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
struct sshbuf {int dummy; } ;

/* Variables and functions */
#define  KEY_DSA 133 
#define  KEY_ECDSA 132 
#define  KEY_ED25519 131 
#define  KEY_RSA 130 
#define  KEY_UNSPEC 129 
#define  KEY_XMSS 128 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 int SSH_ERR_KEY_WRONG_PASSPHRASE ; 
 int sshkey_parse_private2 (struct sshbuf*,int,char const*,struct sshkey**,char**) ; 
 int sshkey_parse_private_pem_fileblob (struct sshbuf*,int,char const*,struct sshkey**) ; 

int
sshkey_parse_private_fileblob_type(struct sshbuf *blob, int type,
    const char *passphrase, struct sshkey **keyp, char **commentp)
{
	int r = SSH_ERR_INTERNAL_ERROR;

	if (keyp != NULL)
		*keyp = NULL;
	if (commentp != NULL)
		*commentp = NULL;

	switch (type) {
#ifdef WITH_OPENSSL
	case KEY_DSA:
	case KEY_ECDSA:
	case KEY_RSA:
		return sshkey_parse_private_pem_fileblob(blob, type,
		    passphrase, keyp);
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
#ifdef WITH_XMSS
	case KEY_XMSS:
#endif /* WITH_XMSS */
		return sshkey_parse_private2(blob, type, passphrase,
		    keyp, commentp);
	case KEY_UNSPEC:
		r = sshkey_parse_private2(blob, type, passphrase, keyp,
		    commentp);
		/* Do not fallback to PEM parser if only passphrase is wrong. */
		if (r == 0 || r == SSH_ERR_KEY_WRONG_PASSPHRASE)
			return r;
#ifdef WITH_OPENSSL
		return sshkey_parse_private_pem_fileblob(blob, type,
		    passphrase, keyp);
#else
		return SSH_ERR_INVALID_FORMAT;
#endif /* WITH_OPENSSL */
	default:
		return SSH_ERR_KEY_TYPE_UNKNOWN;
	}
}