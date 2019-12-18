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
struct s390_paes_ctx {int /*<<< orphan*/  kb; } ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 scalar_t__ __ctr_paes_set_key (struct s390_paes_ctx*) ; 
 int _copy_key_to_kb (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  _free_kb_keybuf (int /*<<< orphan*/ *) ; 
 struct s390_paes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int ctr_paes_set_key(struct crypto_tfm *tfm, const u8 *in_key,
			    unsigned int key_len)
{
	int rc;
	struct s390_paes_ctx *ctx = crypto_tfm_ctx(tfm);

	_free_kb_keybuf(&ctx->kb);
	rc = _copy_key_to_kb(&ctx->kb, in_key, key_len);
	if (rc)
		return rc;

	if (__ctr_paes_set_key(ctx)) {
		tfm->crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
		return -EINVAL;
	}
	return 0;
}