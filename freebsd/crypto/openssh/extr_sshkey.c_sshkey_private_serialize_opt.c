#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sshkey {int type; int /*<<< orphan*/  xmss_sk; int /*<<< orphan*/  xmss_pk; int /*<<< orphan*/ * xmss_name; TYPE_1__* cert; int /*<<< orphan*/  ed25519_sk; int /*<<< orphan*/  ed25519_pk; int /*<<< orphan*/  ecdsa; int /*<<< orphan*/  ecdsa_nid; int /*<<< orphan*/  dsa; int /*<<< orphan*/  rsa; } ;
struct sshbuf {int dummy; } ;
typedef  enum sshkey_serialize_rep { ____Placeholder_sshkey_serialize_rep } sshkey_serialize_rep ;
struct TYPE_2__ {int /*<<< orphan*/  certblob; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  const* EC_KEY_get0_private_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ED25519_PK_SZ ; 
 int /*<<< orphan*/  ED25519_SK_SZ ; 
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
 int /*<<< orphan*/  RSA_get0_crt_params (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  RSA_get0_factors (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  sshbuf_len (int /*<<< orphan*/ ) ; 
 int sshbuf_put_bignum2 (struct sshbuf*,int /*<<< orphan*/  const*) ; 
 int sshbuf_put_cstring (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int sshbuf_put_eckey (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sshbuf_put_stringb (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sshkey_curve_nid_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sshkey_ssh_name (struct sshkey const*) ; 
 int /*<<< orphan*/  sshkey_xmss_pklen (struct sshkey const*) ; 
 int sshkey_xmss_serialize_state_opt (struct sshkey const*,struct sshbuf*,int) ; 
 int /*<<< orphan*/  sshkey_xmss_sklen (struct sshkey const*) ; 

int
sshkey_private_serialize_opt(const struct sshkey *key, struct sshbuf *b,
    enum sshkey_serialize_rep opts)
{
	int r = SSH_ERR_INTERNAL_ERROR;
#ifdef WITH_OPENSSL
	const BIGNUM *rsa_n, *rsa_e, *rsa_d, *rsa_iqmp, *rsa_p, *rsa_q;
	const BIGNUM *dsa_p, *dsa_q, *dsa_g, *dsa_pub_key, *dsa_priv_key;
#endif /* WITH_OPENSSL */

	if ((r = sshbuf_put_cstring(b, sshkey_ssh_name(key))) != 0)
		goto out;
	switch (key->type) {
#ifdef WITH_OPENSSL
	case KEY_RSA:
		RSA_get0_key(key->rsa, &rsa_n, &rsa_e, &rsa_d);
		RSA_get0_factors(key->rsa, &rsa_p, &rsa_q);
		RSA_get0_crt_params(key->rsa, NULL, NULL, &rsa_iqmp);
		if ((r = sshbuf_put_bignum2(b, rsa_n)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_e)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_d)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_iqmp)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_p)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_q)) != 0)
			goto out;
		break;
	case KEY_RSA_CERT:
		if (key->cert == NULL || sshbuf_len(key->cert->certblob) == 0) {
			r = SSH_ERR_INVALID_ARGUMENT;
			goto out;
		}
		RSA_get0_key(key->rsa, NULL, NULL, &rsa_d);
		RSA_get0_factors(key->rsa, &rsa_p, &rsa_q);
		RSA_get0_crt_params(key->rsa, NULL, NULL, &rsa_iqmp);
		if ((r = sshbuf_put_stringb(b, key->cert->certblob)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_d)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_iqmp)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_p)) != 0 ||
		    (r = sshbuf_put_bignum2(b, rsa_q)) != 0)
			goto out;
		break;
	case KEY_DSA:
		DSA_get0_pqg(key->dsa, &dsa_p, &dsa_q, &dsa_g);
		DSA_get0_key(key->dsa, &dsa_pub_key, &dsa_priv_key);
		if ((r = sshbuf_put_bignum2(b, dsa_p)) != 0 ||
		    (r = sshbuf_put_bignum2(b, dsa_q)) != 0 ||
		    (r = sshbuf_put_bignum2(b, dsa_g)) != 0 ||
		    (r = sshbuf_put_bignum2(b, dsa_pub_key)) != 0 ||
		    (r = sshbuf_put_bignum2(b, dsa_priv_key)) != 0)
			goto out;
		break;
	case KEY_DSA_CERT:
		if (key->cert == NULL || sshbuf_len(key->cert->certblob) == 0) {
			r = SSH_ERR_INVALID_ARGUMENT;
			goto out;
		}
		DSA_get0_key(key->dsa, NULL, &dsa_priv_key);
		if ((r = sshbuf_put_stringb(b, key->cert->certblob)) != 0 ||
		    (r = sshbuf_put_bignum2(b, dsa_priv_key)) != 0)
			goto out;
		break;
# ifdef OPENSSL_HAS_ECC
	case KEY_ECDSA:
		if ((r = sshbuf_put_cstring(b,
		    sshkey_curve_nid_to_name(key->ecdsa_nid))) != 0 ||
		    (r = sshbuf_put_eckey(b, key->ecdsa)) != 0 ||
		    (r = sshbuf_put_bignum2(b,
		    EC_KEY_get0_private_key(key->ecdsa))) != 0)
			goto out;
		break;
	case KEY_ECDSA_CERT:
		if (key->cert == NULL || sshbuf_len(key->cert->certblob) == 0) {
			r = SSH_ERR_INVALID_ARGUMENT;
			goto out;
		}
		if ((r = sshbuf_put_stringb(b, key->cert->certblob)) != 0 ||
		    (r = sshbuf_put_bignum2(b,
		    EC_KEY_get0_private_key(key->ecdsa))) != 0)
			goto out;
		break;
# endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */
	case KEY_ED25519:
		if ((r = sshbuf_put_string(b, key->ed25519_pk,
		    ED25519_PK_SZ)) != 0 ||
		    (r = sshbuf_put_string(b, key->ed25519_sk,
		    ED25519_SK_SZ)) != 0)
			goto out;
		break;
	case KEY_ED25519_CERT:
		if (key->cert == NULL || sshbuf_len(key->cert->certblob) == 0) {
			r = SSH_ERR_INVALID_ARGUMENT;
			goto out;
		}
		if ((r = sshbuf_put_stringb(b, key->cert->certblob)) != 0 ||
		    (r = sshbuf_put_string(b, key->ed25519_pk,
		    ED25519_PK_SZ)) != 0 ||
		    (r = sshbuf_put_string(b, key->ed25519_sk,
		    ED25519_SK_SZ)) != 0)
			goto out;
		break;
#ifdef WITH_XMSS
	case KEY_XMSS:
		if (key->xmss_name == NULL) {
			r = SSH_ERR_INVALID_ARGUMENT;
			goto out;
		}
		if ((r = sshbuf_put_cstring(b, key->xmss_name)) != 0 ||
		    (r = sshbuf_put_string(b, key->xmss_pk,
		    sshkey_xmss_pklen(key))) != 0 ||
		    (r = sshbuf_put_string(b, key->xmss_sk,
		    sshkey_xmss_sklen(key))) != 0 ||
		    (r = sshkey_xmss_serialize_state_opt(key, b, opts)) != 0)
			goto out;
		break;
	case KEY_XMSS_CERT:
		if (key->cert == NULL || sshbuf_len(key->cert->certblob) == 0 ||
		    key->xmss_name == NULL) {
			r = SSH_ERR_INVALID_ARGUMENT;
			goto out;
		}
		if ((r = sshbuf_put_stringb(b, key->cert->certblob)) != 0 ||
		    (r = sshbuf_put_cstring(b, key->xmss_name)) != 0 ||
		    (r = sshbuf_put_string(b, key->xmss_pk,
		    sshkey_xmss_pklen(key))) != 0 ||
		    (r = sshbuf_put_string(b, key->xmss_sk,
		    sshkey_xmss_sklen(key))) != 0 ||
		    (r = sshkey_xmss_serialize_state_opt(key, b, opts)) != 0)
			goto out;
		break;
#endif /* WITH_XMSS */
	default:
		r = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}
	/* success */
	r = 0;
 out:
	return r;
}