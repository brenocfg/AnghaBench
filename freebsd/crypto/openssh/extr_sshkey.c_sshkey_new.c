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
struct sshkey {int type; int ecdsa_nid; int /*<<< orphan*/ * cert; int /*<<< orphan*/ * dsa; int /*<<< orphan*/ * rsa; int /*<<< orphan*/ * xmss_pk; int /*<<< orphan*/ * xmss_sk; int /*<<< orphan*/ * ed25519_pk; int /*<<< orphan*/ * ed25519_sk; int /*<<< orphan*/ * ecdsa; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  DSA ;

/* Variables and functions */
 int /*<<< orphan*/ * DSA_new () ; 
#define  KEY_DSA 138 
#define  KEY_DSA_CERT 137 
#define  KEY_ECDSA 136 
#define  KEY_ECDSA_CERT 135 
#define  KEY_ED25519 134 
#define  KEY_ED25519_CERT 133 
#define  KEY_RSA 132 
#define  KEY_RSA_CERT 131 
#define  KEY_UNSPEC 130 
#define  KEY_XMSS 129 
#define  KEY_XMSS_CERT 128 
 int /*<<< orphan*/ * RSA_new () ; 
 struct sshkey* calloc (int,int) ; 
 int /*<<< orphan*/ * cert_new () ; 
 int /*<<< orphan*/  free (struct sshkey*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 scalar_t__ sshkey_is_cert (struct sshkey*) ; 

struct sshkey *
sshkey_new(int type)
{
	struct sshkey *k;
#ifdef WITH_OPENSSL
	RSA *rsa;
	DSA *dsa;
#endif /* WITH_OPENSSL */

	if ((k = calloc(1, sizeof(*k))) == NULL)
		return NULL;
	k->type = type;
	k->ecdsa = NULL;
	k->ecdsa_nid = -1;
	k->dsa = NULL;
	k->rsa = NULL;
	k->cert = NULL;
	k->ed25519_sk = NULL;
	k->ed25519_pk = NULL;
	k->xmss_sk = NULL;
	k->xmss_pk = NULL;
	switch (k->type) {
#ifdef WITH_OPENSSL
	case KEY_RSA:
	case KEY_RSA_CERT:
		if ((rsa = RSA_new()) == NULL) {
			free(k);
			return NULL;
		}
		k->rsa = rsa;
		break;
	case KEY_DSA:
	case KEY_DSA_CERT:
		if ((dsa = DSA_new()) == NULL) {
			free(k);
			return NULL;
		}
		k->dsa = dsa;
		break;
	case KEY_ECDSA:
	case KEY_ECDSA_CERT:
		/* Cannot do anything until we know the group */
		break;
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
	case KEY_ED25519_CERT:
	case KEY_XMSS:
	case KEY_XMSS_CERT:
		/* no need to prealloc */
		break;
	case KEY_UNSPEC:
		break;
	default:
		free(k);
		return NULL;
	}

	if (sshkey_is_cert(k)) {
		if ((k->cert = cert_new()) == NULL) {
			sshkey_free(k);
			return NULL;
		}
	}

	return k;
}