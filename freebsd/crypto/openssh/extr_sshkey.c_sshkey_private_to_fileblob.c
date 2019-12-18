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
struct sshkey {int type; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
#define  KEY_DSA 132 
#define  KEY_ECDSA 131 
#define  KEY_ED25519 130 
#define  KEY_RSA 129 
#define  KEY_XMSS 128 
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 int sshkey_private_pem_to_blob (struct sshkey*,struct sshbuf*,char const*,char const*) ; 
 int sshkey_private_to_blob2 (struct sshkey*,struct sshbuf*,char const*,char const*,char const*,int) ; 

int
sshkey_private_to_fileblob(struct sshkey *key, struct sshbuf *blob,
    const char *passphrase, const char *comment,
    int force_new_format, const char *new_format_cipher, int new_format_rounds)
{
	switch (key->type) {
#ifdef WITH_OPENSSL
	case KEY_DSA:
	case KEY_ECDSA:
	case KEY_RSA:
		if (force_new_format) {
			return sshkey_private_to_blob2(key, blob, passphrase,
			    comment, new_format_cipher, new_format_rounds);
		}
		return sshkey_private_pem_to_blob(key, blob,
		    passphrase, comment);
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
#ifdef WITH_XMSS
	case KEY_XMSS:
#endif /* WITH_XMSS */
		return sshkey_private_to_blob2(key, blob, passphrase,
		    comment, new_format_cipher, new_format_rounds);
	default:
		return SSH_ERR_KEY_TYPE_UNKNOWN;
	}
}