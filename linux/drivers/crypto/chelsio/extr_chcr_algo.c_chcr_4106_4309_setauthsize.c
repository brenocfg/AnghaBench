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
struct crypto_tfm {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct chcr_aead_ctx {int /*<<< orphan*/  sw_cipher; void* mayverify; int /*<<< orphan*/  hmac_ctrl; } ;

/* Variables and functions */
 struct chcr_aead_ctx* AEAD_CTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHCR_SCMD_HMAC_CTRL_DIV2 ; 
 int /*<<< orphan*/  CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT ; 
 int /*<<< orphan*/  CHCR_SCMD_HMAC_CTRL_NO_TRUNC ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
#define  ICV_12 130 
#define  ICV_16 129 
#define  ICV_8 128 
 void* VERIFY_HW ; 
 int /*<<< orphan*/  a_ctx (struct crypto_aead*) ; 
 int crypto_aead_setauthsize (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (struct crypto_tfm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chcr_4106_4309_setauthsize(struct crypto_aead *tfm,
					  unsigned int authsize)
{
	struct chcr_aead_ctx *aeadctx = AEAD_CTX(a_ctx(tfm));

	switch (authsize) {
	case ICV_8:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_DIV2;
		aeadctx->mayverify = VERIFY_HW;
		break;
	case ICV_12:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT;
		aeadctx->mayverify = VERIFY_HW;
		break;
	case ICV_16:
		aeadctx->hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		aeadctx->mayverify = VERIFY_HW;
		break;
	default:
		crypto_tfm_set_flags((struct crypto_tfm *)tfm,
				     CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	return crypto_aead_setauthsize(aeadctx->sw_cipher, authsize);
}