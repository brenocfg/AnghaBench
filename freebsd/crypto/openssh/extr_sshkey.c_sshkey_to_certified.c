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
struct sshkey {int type; int /*<<< orphan*/ * cert; } ;

/* Variables and functions */
#define  KEY_DSA 132 
 int KEY_DSA_CERT ; 
#define  KEY_ECDSA 131 
 int KEY_ECDSA_CERT ; 
#define  KEY_ED25519 130 
 int KEY_ED25519_CERT ; 
#define  KEY_RSA 129 
 int KEY_RSA_CERT ; 
#define  KEY_XMSS 128 
 int KEY_XMSS_CERT ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/ * cert_new () ; 

int
sshkey_to_certified(struct sshkey *k)
{
	int newtype;

	switch (k->type) {
#ifdef WITH_OPENSSL
	case KEY_RSA:
		newtype = KEY_RSA_CERT;
		break;
	case KEY_DSA:
		newtype = KEY_DSA_CERT;
		break;
	case KEY_ECDSA:
		newtype = KEY_ECDSA_CERT;
		break;
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
		newtype = KEY_ED25519_CERT;
		break;
#ifdef WITH_XMSS
	case KEY_XMSS:
		newtype = KEY_XMSS_CERT;
		break;
#endif /* WITH_XMSS */
	default:
		return SSH_ERR_INVALID_ARGUMENT;
	}
	if ((k->cert = cert_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	k->type = newtype;
	return 0;
}