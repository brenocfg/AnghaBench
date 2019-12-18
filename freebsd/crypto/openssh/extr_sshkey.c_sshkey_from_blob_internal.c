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
typedef  char u_char ;
struct sshkey {char* ed25519_pk; char* xmss_pk; int /*<<< orphan*/ * ecdsa; int /*<<< orphan*/  ecdsa_nid; int /*<<< orphan*/  dsa; int /*<<< orphan*/  rsa; } ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  DSA_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DSA_set0_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_set0_pqg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int EC_KEY_set_public_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/ ) ; 
 size_t ED25519_PK_SZ ; 
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
 int /*<<< orphan*/  RSA_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_EC_CURVE_INVALID ; 
 int SSH_ERR_EC_CURVE_MISMATCH ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_CERT_INVALID_SIGN_KEY ; 
 int SSH_ERR_KEY_INVALID_EC_VALUE ; 
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int cert_parse (struct sshbuf*,struct sshkey*,struct sshbuf*) ; 
 int check_rsa_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sshbuf_dump (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_fromb (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_get_bignum2 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_get_cstring (struct sshbuf*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_get_ec (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sshbuf_get_string (struct sshbuf*,char**,size_t*) ; 
 int /*<<< orphan*/  sshbuf_get_string_direct (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/  sshkey_curve_name_to_nid (char*) ; 
 int /*<<< orphan*/  sshkey_dump_ec_point (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshkey_ec_validate_public (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshkey_ecdsa_nid_from_name (char*) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 scalar_t__ sshkey_is_cert (struct sshkey*) ; 
 struct sshkey* sshkey_new (int) ; 
 int sshkey_type_from_name (char*) ; 
 scalar_t__ sshkey_type_is_cert (int) ; 
 int sshkey_xmss_deserialize_pk_info (struct sshkey*,struct sshbuf*) ; 
 int sshkey_xmss_init (struct sshkey*,char*) ; 
 size_t sshkey_xmss_pklen (struct sshkey*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
sshkey_from_blob_internal(struct sshbuf *b, struct sshkey **keyp,
    int allow_cert)
{
	int type, ret = SSH_ERR_INTERNAL_ERROR;
	char *ktype = NULL, *curve = NULL, *xmss_name = NULL;
	struct sshkey *key = NULL;
	size_t len;
	u_char *pk = NULL;
	struct sshbuf *copy;
#if defined(WITH_OPENSSL)
	BIGNUM *rsa_n = NULL, *rsa_e = NULL;
	BIGNUM *dsa_p = NULL, *dsa_q = NULL, *dsa_g = NULL, *dsa_pub_key = NULL;
# if defined(OPENSSL_HAS_ECC)
	EC_POINT *q = NULL;
# endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */

#ifdef DEBUG_PK /* XXX */
	sshbuf_dump(b, stderr);
#endif
	if (keyp != NULL)
		*keyp = NULL;
	if ((copy = sshbuf_fromb(b)) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (sshbuf_get_cstring(b, &ktype, NULL) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}

	type = sshkey_type_from_name(ktype);
	if (!allow_cert && sshkey_type_is_cert(type)) {
		ret = SSH_ERR_KEY_CERT_INVALID_SIGN_KEY;
		goto out;
	}
	switch (type) {
#ifdef WITH_OPENSSL
	case KEY_RSA_CERT:
		/* Skip nonce */
		if (sshbuf_get_string_direct(b, NULL, NULL) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		/* FALLTHROUGH */
	case KEY_RSA:
		if ((key = sshkey_new(type)) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if ((rsa_e = BN_new()) == NULL ||
		    (rsa_n = BN_new()) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if (sshbuf_get_bignum2(b, rsa_e) != 0 ||
		    sshbuf_get_bignum2(b, rsa_n) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		if (!RSA_set0_key(key->rsa, rsa_n, rsa_e, NULL)) {
			ret = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		rsa_n = rsa_e = NULL; /* transferred */
		if ((ret = check_rsa_length(key->rsa)) != 0)
			goto out;
#ifdef DEBUG_PK
		RSA_print_fp(stderr, key->rsa, 8);
#endif
		break;
	case KEY_DSA_CERT:
		/* Skip nonce */
		if (sshbuf_get_string_direct(b, NULL, NULL) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		/* FALLTHROUGH */
	case KEY_DSA:
		if ((key = sshkey_new(type)) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if ((dsa_p = BN_new()) == NULL ||
		    (dsa_q = BN_new()) == NULL ||
		    (dsa_g = BN_new()) == NULL ||
		    (dsa_pub_key = BN_new()) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if (sshbuf_get_bignum2(b, dsa_p) != 0 ||
		    sshbuf_get_bignum2(b, dsa_q) != 0 ||
		    sshbuf_get_bignum2(b, dsa_g) != 0 ||
		    sshbuf_get_bignum2(b, dsa_pub_key) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		if (!DSA_set0_pqg(key->dsa, dsa_p, dsa_q, dsa_g)) {
			ret = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		dsa_p = dsa_q = dsa_g = NULL; /* transferred */
		if (!DSA_set0_key(key->dsa, dsa_pub_key, NULL)) {
			ret = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
		dsa_pub_key = NULL; /* transferred */
#ifdef DEBUG_PK
		DSA_print_fp(stderr, key->dsa, 8);
#endif
		break;
	case KEY_ECDSA_CERT:
		/* Skip nonce */
		if (sshbuf_get_string_direct(b, NULL, NULL) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		/* FALLTHROUGH */
# ifdef OPENSSL_HAS_ECC
	case KEY_ECDSA:
		if ((key = sshkey_new(type)) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		key->ecdsa_nid = sshkey_ecdsa_nid_from_name(ktype);
		if (sshbuf_get_cstring(b, &curve, NULL) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		if (key->ecdsa_nid != sshkey_curve_name_to_nid(curve)) {
			ret = SSH_ERR_EC_CURVE_MISMATCH;
			goto out;
		}
		EC_KEY_free(key->ecdsa);
		if ((key->ecdsa = EC_KEY_new_by_curve_name(key->ecdsa_nid))
		    == NULL) {
			ret = SSH_ERR_EC_CURVE_INVALID;
			goto out;
		}
		if ((q = EC_POINT_new(EC_KEY_get0_group(key->ecdsa))) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if (sshbuf_get_ec(b, q, EC_KEY_get0_group(key->ecdsa)) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		if (sshkey_ec_validate_public(EC_KEY_get0_group(key->ecdsa),
		    q) != 0) {
			ret = SSH_ERR_KEY_INVALID_EC_VALUE;
			goto out;
		}
		if (EC_KEY_set_public_key(key->ecdsa, q) != 1) {
			/* XXX assume it is a allocation error */
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
#ifdef DEBUG_PK
		sshkey_dump_ec_point(EC_KEY_get0_group(key->ecdsa), q);
#endif
		break;
# endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */
	case KEY_ED25519_CERT:
		/* Skip nonce */
		if (sshbuf_get_string_direct(b, NULL, NULL) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		/* FALLTHROUGH */
	case KEY_ED25519:
		if ((ret = sshbuf_get_string(b, &pk, &len)) != 0)
			goto out;
		if (len != ED25519_PK_SZ) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		if ((key = sshkey_new(type)) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		key->ed25519_pk = pk;
		pk = NULL;
		break;
#ifdef WITH_XMSS
	case KEY_XMSS_CERT:
		/* Skip nonce */
		if (sshbuf_get_string_direct(b, NULL, NULL) != 0) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		/* FALLTHROUGH */
	case KEY_XMSS:
		if ((ret = sshbuf_get_cstring(b, &xmss_name, NULL)) != 0)
			goto out;
		if ((key = sshkey_new(type)) == NULL) {
			ret = SSH_ERR_ALLOC_FAIL;
			goto out;
		}
		if ((ret = sshkey_xmss_init(key, xmss_name)) != 0)
			goto out;
		if ((ret = sshbuf_get_string(b, &pk, &len)) != 0)
			goto out;
		if (len == 0 || len != sshkey_xmss_pklen(key)) {
			ret = SSH_ERR_INVALID_FORMAT;
			goto out;
		}
		key->xmss_pk = pk;
		pk = NULL;
		if (type != KEY_XMSS_CERT &&
		    (ret = sshkey_xmss_deserialize_pk_info(key, b)) != 0)
			goto out;
		break;
#endif /* WITH_XMSS */
	case KEY_UNSPEC:
	default:
		ret = SSH_ERR_KEY_TYPE_UNKNOWN;
		goto out;
	}

	/* Parse certificate potion */
	if (sshkey_is_cert(key) && (ret = cert_parse(b, key, copy)) != 0)
		goto out;

	if (key != NULL && sshbuf_len(b) != 0) {
		ret = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	ret = 0;
	if (keyp != NULL) {
		*keyp = key;
		key = NULL;
	}
 out:
	sshbuf_free(copy);
	sshkey_free(key);
	free(xmss_name);
	free(ktype);
	free(curve);
	free(pk);
#if defined(WITH_OPENSSL)
	BN_clear_free(rsa_n);
	BN_clear_free(rsa_e);
	BN_clear_free(dsa_p);
	BN_clear_free(dsa_q);
	BN_clear_free(dsa_g);
	BN_clear_free(dsa_pub_key);
# if defined(OPENSSL_HAS_ECC)
	EC_POINT_free(q);
# endif /* OPENSSL_HAS_ECC */
#endif /* WITH_OPENSSL */
	return ret;
}