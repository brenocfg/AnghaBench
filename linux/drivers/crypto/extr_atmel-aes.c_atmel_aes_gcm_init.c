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
struct crypto_aead {int dummy; } ;
struct atmel_aes_reqctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct atmel_aes_gcm_ctx {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_aes_gcm_start ; 
 struct atmel_aes_gcm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int) ; 

__attribute__((used)) static int atmel_aes_gcm_init(struct crypto_aead *tfm)
{
	struct atmel_aes_gcm_ctx *ctx = crypto_aead_ctx(tfm);

	crypto_aead_set_reqsize(tfm, sizeof(struct atmel_aes_reqctx));
	ctx->base.start = atmel_aes_gcm_start;

	return 0;
}