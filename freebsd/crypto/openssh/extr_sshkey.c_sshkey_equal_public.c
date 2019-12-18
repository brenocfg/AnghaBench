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
struct sshkey {int type; int /*<<< orphan*/ * xmss_pk; int /*<<< orphan*/ * ed25519_pk; int /*<<< orphan*/ * ecdsa; int /*<<< orphan*/ * dsa; int /*<<< orphan*/ * rsa; } ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  EC_GROUP_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ED25519_PK_SZ ; 
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
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sshkey_type_plain (int) ; 
 int /*<<< orphan*/  sshkey_xmss_pklen (struct sshkey const*) ; 

int
sshkey_equal_public(const struct sshkey *a, const struct sshkey *b)
{
#if defined(WITH_OPENSSL)
	const BIGNUM *rsa_e_a, *rsa_n_a;
	const BIGNUM *rsa_e_b, *rsa_n_b;
	const BIGNUM *dsa_p_a, *dsa_q_a, *dsa_g_a, *dsa_pub_key_a;
	const BIGNUM *dsa_p_b, *dsa_q_b, *dsa_g_b, *dsa_pub_key_b;
# if defined(OPENSSL_HAS_ECC)
	BN_CTX *bnctx;
# endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */

	if (a == NULL || b == NULL ||
	    sshkey_type_plain(a->type) != sshkey_type_plain(b->type))
		return 0;

	switch (a->type) {
#ifdef WITH_OPENSSL
	case KEY_RSA_CERT:
	case KEY_RSA:
		if (a->rsa == NULL || b->rsa == NULL)
			return 0;
		RSA_get0_key(a->rsa, &rsa_n_a, &rsa_e_a, NULL);
		RSA_get0_key(b->rsa, &rsa_n_b, &rsa_e_b, NULL);
		return BN_cmp(rsa_e_a, rsa_e_b) == 0 &&
		    BN_cmp(rsa_n_a, rsa_n_b) == 0;
	case KEY_DSA_CERT:
	case KEY_DSA:
		if (a->dsa == NULL || b->dsa == NULL)
			return 0;
		DSA_get0_pqg(a->dsa, &dsa_p_a, &dsa_q_a, &dsa_g_a);
		DSA_get0_pqg(b->dsa, &dsa_p_b, &dsa_q_b, &dsa_g_b);
		DSA_get0_key(a->dsa, &dsa_pub_key_a, NULL);
		DSA_get0_key(b->dsa, &dsa_pub_key_b, NULL);
		return BN_cmp(dsa_p_a, dsa_p_b) == 0 &&
		    BN_cmp(dsa_q_a, dsa_q_b) == 0 &&
		    BN_cmp(dsa_g_a, dsa_g_b) == 0 &&
		    BN_cmp(dsa_pub_key_a, dsa_pub_key_b) == 0;
# ifdef OPENSSL_HAS_ECC
	case KEY_ECDSA_CERT:
	case KEY_ECDSA:
		if (a->ecdsa == NULL || b->ecdsa == NULL ||
		    EC_KEY_get0_public_key(a->ecdsa) == NULL ||
		    EC_KEY_get0_public_key(b->ecdsa) == NULL)
			return 0;
		if ((bnctx = BN_CTX_new()) == NULL)
			return 0;
		if (EC_GROUP_cmp(EC_KEY_get0_group(a->ecdsa),
		    EC_KEY_get0_group(b->ecdsa), bnctx) != 0 ||
		    EC_POINT_cmp(EC_KEY_get0_group(a->ecdsa),
		    EC_KEY_get0_public_key(a->ecdsa),
		    EC_KEY_get0_public_key(b->ecdsa), bnctx) != 0) {
			BN_CTX_free(bnctx);
			return 0;
		}
		BN_CTX_free(bnctx);
		return 1;
# endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
	case KEY_ED25519_CERT:
		return a->ed25519_pk != NULL && b->ed25519_pk != NULL &&
		    memcmp(a->ed25519_pk, b->ed25519_pk, ED25519_PK_SZ) == 0;
#ifdef WITH_XMSS
	case KEY_XMSS:
	case KEY_XMSS_CERT:
		return a->xmss_pk != NULL && b->xmss_pk != NULL &&
		    sshkey_xmss_pklen(a) == sshkey_xmss_pklen(b) &&
		    memcmp(a->xmss_pk, b->xmss_pk, sshkey_xmss_pklen(a)) == 0;
#endif /* WITH_XMSS */
	default:
		return 0;
	}
	/* NOTREACHED */
}