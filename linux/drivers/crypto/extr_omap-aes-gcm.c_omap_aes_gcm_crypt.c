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
typedef  int /*<<< orphan*/  u32 ;
struct omap_aes_reqctx {unsigned long mode; scalar_t__ auth_tag; scalar_t__ iv; } ;
struct omap_aes_dev {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int assoclen; scalar_t__ cryptlen; int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENODEV ; 
 unsigned long FLAGS_RFC4106_GCM ; 
 scalar_t__ GCM_AES_IV_SIZE ; 
 struct omap_aes_reqctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int do_encrypt_iv (struct aead_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct omap_aes_dev* omap_aes_find_dev (struct omap_aes_reqctx*) ; 
 int omap_aes_gcm_handle_queue (struct omap_aes_dev*,struct aead_request*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int omap_aes_gcm_crypt(struct aead_request *req, unsigned long mode)
{
	struct omap_aes_reqctx *rctx = aead_request_ctx(req);
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	unsigned int authlen = crypto_aead_authsize(aead);
	struct omap_aes_dev *dd;
	__be32 counter = cpu_to_be32(1);
	int err, assoclen;

	memset(rctx->auth_tag, 0, sizeof(rctx->auth_tag));
	memcpy(rctx->iv + GCM_AES_IV_SIZE, &counter, 4);

	err = do_encrypt_iv(req, (u32 *)rctx->auth_tag, (u32 *)rctx->iv);
	if (err)
		return err;

	if (mode & FLAGS_RFC4106_GCM)
		assoclen = req->assoclen - 8;
	else
		assoclen = req->assoclen;
	if (assoclen + req->cryptlen == 0) {
		scatterwalk_map_and_copy(rctx->auth_tag, req->dst, 0, authlen,
					 1);
		return 0;
	}

	dd = omap_aes_find_dev(rctx);
	if (!dd)
		return -ENODEV;
	rctx->mode = mode;

	return omap_aes_gcm_handle_queue(dd, req);
}