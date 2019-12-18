#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void const u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct ecrdsa_ctx {char* digest; int digest_len; int key_len; TYPE_3__ pub_key; TYPE_2__* curve; scalar_t__ key; int /*<<< orphan*/ * _pubp; scalar_t__ algo_oid; int /*<<< orphan*/  digest_oid; } ;
struct crypto_akcipher {int dummy; } ;
struct TYPE_5__ {int ndigits; } ;
struct TYPE_6__ {TYPE_1__ g; } ;

/* Variables and functions */
 TYPE_3__ ECC_POINT_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int EKEYREJECTED ; 
 int ENOPKG ; 
 int /*<<< orphan*/  OID_gost2012Digest256 ; 
 int /*<<< orphan*/  OID_gost2012Digest512 ; 
 scalar_t__ OID_gost2012PKey256 ; 
 scalar_t__ OID_gost2012PKey512 ; 
 struct ecrdsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int asn1_ber_decoder (int /*<<< orphan*/ *,struct ecrdsa_ctx*,void const*,scalar_t__) ; 
 scalar_t__ ecc_is_pubkey_valid_partial (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ecrdsa_params_decoder ; 
 int /*<<< orphan*/  ecrdsa_pub_key_decoder ; 
 void const* ecrdsa_unpack_u32 (scalar_t__*,void const*) ; 
 int /*<<< orphan*/  vli_from_le64 (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int ecrdsa_set_pub_key(struct crypto_akcipher *tfm, const void *key,
			      unsigned int keylen)
{
	struct ecrdsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	unsigned int ndigits;
	u32 algo, paramlen;
	u8 *params;
	int err;

	err = asn1_ber_decoder(&ecrdsa_pub_key_decoder, ctx, key, keylen);
	if (err < 0)
		return err;

	/* Key parameters is in the key after keylen. */
	params = ecrdsa_unpack_u32(&paramlen,
			  ecrdsa_unpack_u32(&algo, (u8 *)key + keylen));

	if (algo == OID_gost2012PKey256) {
		ctx->digest	= "streebog256";
		ctx->digest_oid	= OID_gost2012Digest256;
		ctx->digest_len	= 256 / 8;
	} else if (algo == OID_gost2012PKey512) {
		ctx->digest	= "streebog512";
		ctx->digest_oid	= OID_gost2012Digest512;
		ctx->digest_len	= 512 / 8;
	} else
		return -ENOPKG;
	ctx->algo_oid = algo;

	/* Parse SubjectPublicKeyInfo.AlgorithmIdentifier.parameters. */
	err = asn1_ber_decoder(&ecrdsa_params_decoder, ctx, params, paramlen);
	if (err < 0)
		return err;
	/*
	 * Sizes of algo (set in digest_len) and curve should match
	 * each other.
	 */
	if (!ctx->curve ||
	    ctx->curve->g.ndigits * sizeof(u64) != ctx->digest_len)
		return -ENOPKG;
	/*
	 * Key is two 256- or 512-bit coordinates which should match
	 * curve size.
	 */
	if ((ctx->key_len != (2 * 256 / 8) &&
	     ctx->key_len != (2 * 512 / 8)) ||
	    ctx->key_len != ctx->curve->g.ndigits * sizeof(u64) * 2)
		return -ENOPKG;

	ndigits = ctx->key_len / sizeof(u64) / 2;
	ctx->pub_key = ECC_POINT_INIT(ctx->_pubp[0], ctx->_pubp[1], ndigits);
	vli_from_le64(ctx->pub_key.x, ctx->key, ndigits);
	vli_from_le64(ctx->pub_key.y, ctx->key + ndigits * sizeof(u64),
		      ndigits);

	if (ecc_is_pubkey_valid_partial(ctx->curve, &ctx->pub_key))
		return -EKEYREJECTED;

	return 0;
}