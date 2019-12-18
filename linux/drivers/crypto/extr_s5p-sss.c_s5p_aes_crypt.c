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
struct s5p_aes_reqctx {unsigned long mode; } ;
struct s5p_aes_dev {int /*<<< orphan*/  dev; } ;
struct s5p_aes_ctx {struct s5p_aes_dev* dev; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int EINVAL ; 
 unsigned long FLAGS_AES_CTR ; 
 unsigned long FLAGS_AES_MODE_MASK ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s5p_aes_reqctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 struct s5p_aes_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int s5p_aes_handle_req (struct s5p_aes_dev*,struct ablkcipher_request*) ; 

__attribute__((used)) static int s5p_aes_crypt(struct ablkcipher_request *req, unsigned long mode)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct s5p_aes_reqctx *reqctx = ablkcipher_request_ctx(req);
	struct s5p_aes_ctx *ctx = crypto_ablkcipher_ctx(tfm);
	struct s5p_aes_dev *dev = ctx->dev;

	if (!req->nbytes)
		return 0;

	if (!IS_ALIGNED(req->nbytes, AES_BLOCK_SIZE) &&
			((mode & FLAGS_AES_MODE_MASK) != FLAGS_AES_CTR)) {
		dev_dbg(dev->dev, "request size is not exact amount of AES blocks\n");
		return -EINVAL;
	}

	reqctx->mode = mode;

	return s5p_aes_handle_req(dev, req);
}