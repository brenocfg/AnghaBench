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
typedef  int /*<<< orphan*/  u8 ;
struct s390_pxts_ctx {TYPE_1__* pk; int /*<<< orphan*/ * kb; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  protkey; } ;

/* Variables and functions */
 unsigned int AES_KEYSIZE_128 ; 
 unsigned int AES_KEYSIZE_256 ; 
 int AES_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 scalar_t__ PKEY_KEYTYPE_AES_128 ; 
 scalar_t__ __xts_paes_set_key (struct s390_pxts_ctx*) ; 
 int _copy_key_to_kb (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  _free_kb_keybuf (int /*<<< orphan*/ *) ; 
 struct s390_pxts_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int xts_check_key (struct crypto_tfm*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int xts_paes_set_key(struct crypto_tfm *tfm, const u8 *in_key,
			    unsigned int xts_key_len)
{
	int rc;
	struct s390_pxts_ctx *ctx = crypto_tfm_ctx(tfm);
	u8 ckey[2 * AES_MAX_KEY_SIZE];
	unsigned int ckey_len, key_len;

	if (xts_key_len % 2)
		return -EINVAL;

	key_len = xts_key_len / 2;

	_free_kb_keybuf(&ctx->kb[0]);
	_free_kb_keybuf(&ctx->kb[1]);
	rc = _copy_key_to_kb(&ctx->kb[0], in_key, key_len);
	if (rc)
		return rc;
	rc = _copy_key_to_kb(&ctx->kb[1], in_key + key_len, key_len);
	if (rc)
		return rc;

	if (__xts_paes_set_key(ctx)) {
		tfm->crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}

	/*
	 * xts_check_key verifies the key length is not odd and makes
	 * sure that the two keys are not the same. This can be done
	 * on the two protected keys as well
	 */
	ckey_len = (ctx->pk[0].type == PKEY_KEYTYPE_AES_128) ?
		AES_KEYSIZE_128 : AES_KEYSIZE_256;
	memcpy(ckey, ctx->pk[0].protkey, ckey_len);
	memcpy(ckey + ckey_len, ctx->pk[1].protkey, ckey_len);
	return xts_check_key(tfm, ckey, 2*ckey_len);
}