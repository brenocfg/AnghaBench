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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_rsa_key {int private_key; struct bignum* iqmp; struct bignum* dmq1; struct bignum* dmp1; struct bignum* q; struct bignum* p; struct bignum* d; struct bignum* e; struct bignum* n; } ;
struct bignum {int dummy; } ;
struct asn1_hdr {scalar_t__ class; scalar_t__ tag; int length; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 scalar_t__ ASN1_CLASS_UNIVERSAL ; 
 scalar_t__ ASN1_TAG_SEQUENCE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ asn1_get_next (int /*<<< orphan*/  const*,size_t,struct asn1_hdr*) ; 
 scalar_t__ bignum_cmp_d (struct bignum*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bignum_deinit (struct bignum*) ; 
 void* bignum_init () ; 
 int /*<<< orphan*/  crypto_rsa_free (struct crypto_rsa_key*) ; 
 int /*<<< orphan*/ * crypto_rsa_parse_integer (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct bignum*) ; 
 struct crypto_rsa_key* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct crypto_rsa_key *
crypto_rsa_import_private_key(const u8 *buf, size_t len)
{
	struct crypto_rsa_key *key;
	struct bignum *zero;
	struct asn1_hdr hdr;
	const u8 *pos, *end;

	key = os_zalloc(sizeof(*key));
	if (key == NULL)
		return NULL;

	key->private_key = 1;

	key->n = bignum_init();
	key->e = bignum_init();
	key->d = bignum_init();
	key->p = bignum_init();
	key->q = bignum_init();
	key->dmp1 = bignum_init();
	key->dmq1 = bignum_init();
	key->iqmp = bignum_init();

	if (key->n == NULL || key->e == NULL || key->d == NULL ||
	    key->p == NULL || key->q == NULL || key->dmp1 == NULL ||
	    key->dmq1 == NULL || key->iqmp == NULL) {
		crypto_rsa_free(key);
		return NULL;
	}

	/*
	 * PKCS #1, 7.2:
	 * RSAPrivateKey ::= SEQUENCE {
	 *    version Version,
	 *    modulus INTEGER, -- n
	 *    publicExponent INTEGER, -- e
	 *    privateExponent INTEGER, -- d
	 *    prime1 INTEGER, -- p
	 *    prime2 INTEGER, -- q
	 *    exponent1 INTEGER, -- d mod (p-1)
	 *    exponent2 INTEGER, -- d mod (q-1)
	 *    coefficient INTEGER -- (inverse of q) mod p
	 * }
	 *
	 * Version ::= INTEGER -- shall be 0 for this version of the standard
	 */
	if (asn1_get_next(buf, len, &hdr) < 0 ||
	    hdr.class != ASN1_CLASS_UNIVERSAL ||
	    hdr.tag != ASN1_TAG_SEQUENCE) {
		wpa_printf(MSG_DEBUG, "RSA: Expected SEQUENCE "
			   "(public key) - found class %d tag 0x%x",
			   hdr.class, hdr.tag);
		goto error;
	}
	pos = hdr.payload;
	end = pos + hdr.length;

	zero = bignum_init();
	if (zero == NULL)
		goto error;
	pos = crypto_rsa_parse_integer(pos, end, zero);
	if (pos == NULL || bignum_cmp_d(zero, 0) != 0) {
		wpa_printf(MSG_DEBUG, "RSA: Expected zero INTEGER in the "
			   "beginning of private key; not found");
		bignum_deinit(zero);
		goto error;
	}
	bignum_deinit(zero);

	pos = crypto_rsa_parse_integer(pos, end, key->n);
	pos = crypto_rsa_parse_integer(pos, end, key->e);
	pos = crypto_rsa_parse_integer(pos, end, key->d);
	pos = crypto_rsa_parse_integer(pos, end, key->p);
	pos = crypto_rsa_parse_integer(pos, end, key->q);
	pos = crypto_rsa_parse_integer(pos, end, key->dmp1);
	pos = crypto_rsa_parse_integer(pos, end, key->dmq1);
	pos = crypto_rsa_parse_integer(pos, end, key->iqmp);

	if (pos == NULL)
		goto error;

	if (pos != end) {
		wpa_hexdump(MSG_DEBUG,
			    "RSA: Extra data in public key SEQUENCE",
			    pos, end - pos);
		goto error;
	}

	return key;

error:
	crypto_rsa_free(key);
	return NULL;
}