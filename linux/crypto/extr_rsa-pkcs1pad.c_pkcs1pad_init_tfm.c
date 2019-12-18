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
struct pkcs1pad_inst_ctx {int /*<<< orphan*/  spawn; } ;
struct pkcs1pad_ctx {struct crypto_akcipher* child; } ;
struct crypto_akcipher {int dummy; } ;
struct akcipher_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_akcipher*) ; 
 int PTR_ERR (struct crypto_akcipher*) ; 
 struct akcipher_instance* akcipher_alg_instance (struct crypto_akcipher*) ; 
 struct pkcs1pad_inst_ctx* akcipher_instance_ctx (struct akcipher_instance*) ; 
 struct pkcs1pad_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 struct crypto_akcipher* crypto_spawn_akcipher (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkcs1pad_init_tfm(struct crypto_akcipher *tfm)
{
	struct akcipher_instance *inst = akcipher_alg_instance(tfm);
	struct pkcs1pad_inst_ctx *ictx = akcipher_instance_ctx(inst);
	struct pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct crypto_akcipher *child_tfm;

	child_tfm = crypto_spawn_akcipher(&ictx->spawn);
	if (IS_ERR(child_tfm))
		return PTR_ERR(child_tfm);

	ctx->child = child_tfm;
	return 0;
}