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
struct skcipherd_instance_ctx {int /*<<< orphan*/  spawn; } ;
struct skcipher_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_drop_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct skcipher_instance*) ; 
 struct skcipherd_instance_ctx* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static void cryptd_skcipher_free(struct skcipher_instance *inst)
{
	struct skcipherd_instance_ctx *ctx = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(&ctx->spawn);
	kfree(inst);
}