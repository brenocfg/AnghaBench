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
struct des_ctx {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DIR_DECRYPT ; 
 struct des_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int lq_queue_mgr (struct des_ctx*,struct ablkcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lq_ecb_des_decrypt(struct ablkcipher_request *areq)
{
    struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(areq);
    struct des_ctx *ctx = crypto_ablkcipher_ctx(cipher);

    return lq_queue_mgr(ctx, areq, areq->info, CRYPTO_DIR_DECRYPT, 0);

}