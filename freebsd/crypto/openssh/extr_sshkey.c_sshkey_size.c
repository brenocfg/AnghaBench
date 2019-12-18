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
typedef  int u_int ;
struct sshkey {int type; int /*<<< orphan*/  ecdsa_nid; int /*<<< orphan*/ * dsa; int /*<<< orphan*/ * rsa; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  KEY_DSA 137 
#define  KEY_DSA_CERT 136 
#define  KEY_ECDSA 135 
#define  KEY_ECDSA_CERT 134 
#define  KEY_ED25519 133 
#define  KEY_ED25519_CERT 132 
#define  KEY_RSA 131 
#define  KEY_RSA_CERT 130 
#define  KEY_XMSS 129 
#define  KEY_XMSS_CERT 128 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sshkey_curve_nid_to_bits (int /*<<< orphan*/ ) ; 

u_int
sshkey_size(const struct sshkey *k)
{
#ifdef WITH_OPENSSL
	const BIGNUM *rsa_n, *dsa_p;
#endif /* WITH_OPENSSL */

	switch (k->type) {
#ifdef WITH_OPENSSL
	case KEY_RSA:
	case KEY_RSA_CERT:
		if (k->rsa == NULL)
			return 0;
		RSA_get0_key(k->rsa, &rsa_n, NULL, NULL);
		return BN_num_bits(rsa_n);
	case KEY_DSA:
	case KEY_DSA_CERT:
		if (k->dsa == NULL)
			return 0;
		DSA_get0_pqg(k->dsa, &dsa_p, NULL, NULL);
		return BN_num_bits(dsa_p);
	case KEY_ECDSA:
	case KEY_ECDSA_CERT:
		return sshkey_curve_nid_to_bits(k->ecdsa_nid);
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
	case KEY_ED25519_CERT:
	case KEY_XMSS:
	case KEY_XMSS_CERT:
		return 256;	/* XXX */
	}
	return 0;
}