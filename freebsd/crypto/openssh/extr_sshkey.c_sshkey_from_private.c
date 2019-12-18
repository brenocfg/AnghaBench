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
typedef  struct sshkey {int type; int /*<<< orphan*/ * xmss_pk; int /*<<< orphan*/  xmss_name; int /*<<< orphan*/ * ed25519_pk; int /*<<< orphan*/  rsa; int /*<<< orphan*/ * ecdsa; int /*<<< orphan*/  ecdsa_nid; int /*<<< orphan*/  dsa; } const sshkey ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DSA_set0_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_set0_pqg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int EC_KEY_set_public_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ED25519_PK_SZ ; 
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
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int sshkey_cert_copy (struct sshkey const*,struct sshkey const*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey const*) ; 
 scalar_t__ sshkey_is_cert (struct sshkey const*) ; 
 struct sshkey const* sshkey_new (int) ; 
 int sshkey_xmss_init (struct sshkey const*,int /*<<< orphan*/ ) ; 
 size_t sshkey_xmss_pklen (struct sshkey const*) ; 

int
sshkey_from_private(const struct sshkey *k, struct sshkey **pkp)
{
	struct sshkey *n = NULL;
	int r = SSH_ERR_INTERNAL_ERROR;
#ifdef WITH_OPENSSL
	const BIGNUM *rsa_n, *rsa_e;
	BIGNUM *rsa_n_dup = NULL, *rsa_e_dup = NULL;
	const BIGNUM *dsa_p, *dsa_q, *dsa_g, *dsa_pub_key;
	BIGNUM *dsa_p_dup = NULL, *dsa_q_dup = NULL, *dsa_g_dup = NULL;
	BIGNUM *dsa_pub_key_dup = NULL;
#endif /* WITH_OPENSSL */

	*pkp = NULL;
	switch (k->type) {
#ifdef WITH_OPENSSL
	case KEY_DSA:
	case KEY_DSA_CERT:
		if ((n = sshkey_new(k->type)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}

		DSA_get0_pqg(k->dsa, &dsa_p, &dsa_q, &dsa_g);
		DSA_get0_key(k->dsa, &dsa_pub_key, NULL);
		if ((dsa_p_dup = BN_dup(dsa_p)) == NULL ||
		    (dsa_q_dup = BN_dup(dsa_q)) == NULL ||
		    (dsa_g_dup = BN_dup(dsa_g)) == NULL ||
		    (dsa_pub_key_dup = BN_dup(dsa_pub_key)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if (!DSA_set0_pqg(n->dsa, dsa_p_dup, dsa_q_dup, dsa_g_dup)) {
			r = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		dsa_p_dup = dsa_q_dup = dsa_g_dup = NULL; /* transferred */
		if (!DSA_set0_key(n->dsa, dsa_pub_key_dup, NULL)) {
			r = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		dsa_pub_key_dup = NULL; /* transferred */

		break;
# ifdef OPENSSL_HAS_ECC
	case KEY_ECDSA:
	case KEY_ECDSA_CERT:
		if ((n = sshkey_new(k->type)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		n->ecdsa_nid = k->ecdsa_nid;
		n->ecdsa = EC_KEY_new_by_curve_name(k->ecdsa_nid);
		if (n->ecdsa == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if (EC_KEY_set_public_key(n->ecdsa,
		    EC_KEY_get0_public_key(k->ecdsa)) != 1) {
			r = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		break;
# endif /* OPENSSL_HAS_ECC */
	case KEY_RSA:
	case KEY_RSA_CERT:
		if ((n = sshkey_new(k->type)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		RSA_get0_key(k->rsa, &rsa_n, &rsa_e, NULL);
		if ((rsa_n_dup = BN_dup(rsa_n)) == NULL ||
		    (rsa_e_dup = BN_dup(rsa_e)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if (!RSA_set0_key(n->rsa, rsa_n_dup, rsa_e_dup, NULL)) {
			r = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		rsa_n_dup = rsa_e_dup = NULL; /* transferred */
		break;
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
	case KEY_ED25519_CERT:
		if ((n = sshkey_new(k->type)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if (k->ed25519_pk != NULL) {
			if ((n->ed25519_pk = malloc(ED25519_PK_SZ)) == NULL) {
				r = SSH_ERR_ALLOC_FAIL;
				goto out;
			}
			memcpy(n->ed25519_pk, k->ed25519_pk, ED25519_PK_SZ);
		}
		break;
#ifdef WITH_XMSS
	case KEY_XMSS:
	case KEY_XMSS_CERT:
		if ((n = sshkey_new(k->type)) == NULL) {
			r = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if ((r = sshkey_xmss_init(n, k->xmss_name)) != 0)
			goto out;
		if (k->xmss_pk != NULL) {
			size_t pklen = sshkey_xmss_pklen(k);
			if (pklen == 0 || sshkey_xmss_pklen(n) != pklen) {
				r = SSH_ERR_INTERNAL_ERROR;
				goto out;
			}
			if ((n->xmss_pk = malloc(pklen)) == NULL) {
				r = SSH_ERR_ALLOC_FAIL;
				goto out;
			}
			memcpy(n->xmss_pk, k->xmss_pk, pklen);
		}
		break;
#endif /* WITH_XMSS */
	default:
		r = SSH_ERR_KEY_TYPE_UNKNOWN;
		goto out;
	}
	if (sshkey_is_cert(k) && (r = sshkey_cert_copy(k, n)) != 0)
		goto out;
	/* success */
	*pkp = n;
	n = NULL;
	r = 0;
 out:
	sshkey_free(n);
#ifdef WITH_OPENSSL
	BN_clear_free(rsa_n_dup);
	BN_clear_free(rsa_e_dup);
	BN_clear_free(dsa_p_dup);
	BN_clear_free(dsa_q_dup);
	BN_clear_free(dsa_g_dup);
	BN_clear_free(dsa_pub_key_dup);
#endif

	return r;
}