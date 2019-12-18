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
typedef  int /*<<< orphan*/  u64 ;
struct ecdh_ctx {unsigned int ndigits; int /*<<< orphan*/  private_key; int /*<<< orphan*/  curve_id; } ;
struct ecdh {int /*<<< orphan*/  key_size; scalar_t__ key; int /*<<< orphan*/  curve_id; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ crypto_ecdh_decode_key (void const*,unsigned int,struct ecdh*) ; 
 int ecc_gen_privkey (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ecc_is_key_valid (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct ecdh_ctx* ecdh_get_ctx (struct crypto_kpp*) ; 
 unsigned int ecdh_supported_curve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecdh_set_secret(struct crypto_kpp *tfm, const void *buf,
			   unsigned int len)
{
	struct ecdh_ctx *ctx = ecdh_get_ctx(tfm);
	struct ecdh params;
	unsigned int ndigits;

	if (crypto_ecdh_decode_key(buf, len, &params) < 0)
		return -EINVAL;

	ndigits = ecdh_supported_curve(params.curve_id);
	if (!ndigits)
		return -EINVAL;

	ctx->curve_id = params.curve_id;
	ctx->ndigits = ndigits;

	if (!params.key || !params.key_size)
		return ecc_gen_privkey(ctx->curve_id, ctx->ndigits,
				       ctx->private_key);

	if (ecc_is_key_valid(ctx->curve_id, ctx->ndigits,
			     (const u64 *)params.key, params.key_size) < 0)
		return -EINVAL;

	memcpy(ctx->private_key, params.key, params.key_size);

	return 0;
}