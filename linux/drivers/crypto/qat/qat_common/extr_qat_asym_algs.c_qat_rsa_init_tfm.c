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
struct qat_rsa_ctx {struct qat_crypto_instance* inst; scalar_t__ key_sz; } ;
struct qat_crypto_instance {int dummy; } ;
struct crypto_akcipher {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct qat_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  get_current_node () ; 
 struct qat_crypto_instance* qat_crypto_get_instance_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_rsa_init_tfm(struct crypto_akcipher *tfm)
{
	struct qat_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct qat_crypto_instance *inst =
			qat_crypto_get_instance_node(get_current_node());

	if (!inst)
		return -EINVAL;

	ctx->key_sz = 0;
	ctx->inst = inst;
	return 0;
}