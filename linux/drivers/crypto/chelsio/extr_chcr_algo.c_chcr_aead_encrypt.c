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
struct crypto_aead {int dummy; } ;
struct chcr_aead_reqctx {int /*<<< orphan*/  op; int /*<<< orphan*/  verify; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR_ENCRYPT_OP ; 
#define  CRYPTO_ALG_SUB_TYPE_AEAD_CCM 133 
#define  CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309 132 
#define  CRYPTO_ALG_SUB_TYPE_CBC_NULL 131 
#define  CRYPTO_ALG_SUB_TYPE_CBC_SHA 130 
#define  CRYPTO_ALG_SUB_TYPE_CTR_NULL 129 
#define  CRYPTO_ALG_SUB_TYPE_CTR_SHA 128 
 int /*<<< orphan*/  VERIFY_HW ; 
 struct chcr_aead_reqctx* aead_request_ctx (struct aead_request*) ; 
 int chcr_aead_op (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_aead_ccm_wr ; 
 int /*<<< orphan*/  create_authenc_wr ; 
 int /*<<< orphan*/  create_gcm_wr ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int get_aead_subtype (struct crypto_aead*) ; 

__attribute__((used)) static int chcr_aead_encrypt(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct chcr_aead_reqctx *reqctx = aead_request_ctx(req);

	reqctx->verify = VERIFY_HW;
	reqctx->op = CHCR_ENCRYPT_OP;

	switch (get_aead_subtype(tfm)) {
	case CRYPTO_ALG_SUB_TYPE_CTR_SHA:
	case CRYPTO_ALG_SUB_TYPE_CBC_SHA:
	case CRYPTO_ALG_SUB_TYPE_CBC_NULL:
	case CRYPTO_ALG_SUB_TYPE_CTR_NULL:
		return chcr_aead_op(req, 0, create_authenc_wr);
	case CRYPTO_ALG_SUB_TYPE_AEAD_CCM:
	case CRYPTO_ALG_SUB_TYPE_AEAD_RFC4309:
		return chcr_aead_op(req, 0, create_aead_ccm_wr);
	default:
		return chcr_aead_op(req, 0, create_gcm_wr);
	}
}