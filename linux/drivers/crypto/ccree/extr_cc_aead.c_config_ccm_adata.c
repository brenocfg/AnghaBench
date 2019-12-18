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
typedef  int u8 ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_aead_ctx {unsigned int authsize; int /*<<< orphan*/  drvdata; } ;
struct aead_request {unsigned int* iv; unsigned int cryptlen; } ;
struct TYPE_2__ {scalar_t__ op_type; } ;
struct aead_req_ctx {int* ccm_config; int* mac_buf; scalar_t__ assoclen; int /*<<< orphan*/  ccm_hdr_size; TYPE_1__ gen_ctx; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int CCM_A0_OFFSET ; 
 int CCM_B0_OFFSET ; 
 int CCM_CTR_COUNT_0_OFFSET ; 
 scalar_t__ DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int EINVAL ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_ccm_a0 (int*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int set_msg_len (int*,unsigned int,unsigned int) ; 

__attribute__((used)) static int config_ccm_adata(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	//unsigned int size_of_a = 0, rem_a_size = 0;
	unsigned int lp = req->iv[0];
	/* Note: The code assume that req->iv[0] already contains the value
	 * of L' of RFC3610
	 */
	unsigned int l = lp + 1;  /* This is L' of RFC 3610. */
	unsigned int m = ctx->authsize;  /* This is M' of RFC 3610. */
	u8 *b0 = req_ctx->ccm_config + CCM_B0_OFFSET;
	u8 *a0 = req_ctx->ccm_config + CCM_A0_OFFSET;
	u8 *ctr_count_0 = req_ctx->ccm_config + CCM_CTR_COUNT_0_OFFSET;
	unsigned int cryptlen = (req_ctx->gen_ctx.op_type ==
				 DRV_CRYPTO_DIRECTION_ENCRYPT) ?
				req->cryptlen :
				(req->cryptlen - ctx->authsize);
	int rc;

	memset(req_ctx->mac_buf, 0, AES_BLOCK_SIZE);
	memset(req_ctx->ccm_config, 0, AES_BLOCK_SIZE * 3);

	/* taken from crypto/ccm.c */
	/* 2 <= L <= 8, so 1 <= L' <= 7. */
	if (l < 2 || l > 8) {
		dev_err(dev, "illegal iv value %X\n", req->iv[0]);
		return -EINVAL;
	}
	memcpy(b0, req->iv, AES_BLOCK_SIZE);

	/* format control info per RFC 3610 and
	 * NIST Special Publication 800-38C
	 */
	*b0 |= (8 * ((m - 2) / 2));
	if (req_ctx->assoclen > 0)
		*b0 |= 64;  /* Enable bit 6 if Adata exists. */

	rc = set_msg_len(b0 + 16 - l, cryptlen, l);  /* Write L'. */
	if (rc) {
		dev_err(dev, "message len overflow detected");
		return rc;
	}
	 /* END of "taken from crypto/ccm.c" */

	/* l(a) - size of associated data. */
	req_ctx->ccm_hdr_size = format_ccm_a0(a0, req_ctx->assoclen);

	memset(req->iv + 15 - req->iv[0], 0, req->iv[0] + 1);
	req->iv[15] = 1;

	memcpy(ctr_count_0, req->iv, AES_BLOCK_SIZE);
	ctr_count_0[15] = 0;

	return 0;
}