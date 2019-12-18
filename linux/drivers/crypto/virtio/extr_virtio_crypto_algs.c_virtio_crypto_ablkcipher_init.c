#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtio_crypto_sym_request {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * unprepare_request; int /*<<< orphan*/ * prepare_request; int /*<<< orphan*/  do_one_request; } ;
struct TYPE_5__ {TYPE_3__ op; } ;
struct virtio_crypto_ablkcipher_ctx {TYPE_2__ enginectx; struct crypto_tfm* tfm; } ;
struct TYPE_4__ {int reqsize; } ;
struct crypto_tfm {TYPE_1__ crt_ablkcipher; } ;

/* Variables and functions */
 struct virtio_crypto_ablkcipher_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  virtio_crypto_ablkcipher_crypt_req ; 

__attribute__((used)) static int virtio_crypto_ablkcipher_init(struct crypto_tfm *tfm)
{
	struct virtio_crypto_ablkcipher_ctx *ctx = crypto_tfm_ctx(tfm);

	tfm->crt_ablkcipher.reqsize = sizeof(struct virtio_crypto_sym_request);
	ctx->tfm = tfm;

	ctx->enginectx.op.do_one_request = virtio_crypto_ablkcipher_crypt_req;
	ctx->enginectx.op.prepare_request = NULL;
	ctx->enginectx.op.unprepare_request = NULL;
	return 0;
}