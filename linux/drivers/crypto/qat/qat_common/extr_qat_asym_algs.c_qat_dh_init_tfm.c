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
struct qat_dh_ctx {int g2; struct qat_crypto_instance* inst; scalar_t__ p_size; } ;
struct qat_crypto_instance {int dummy; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  get_current_node () ; 
 struct qat_dh_ctx* kpp_tfm_ctx (struct crypto_kpp*) ; 
 struct qat_crypto_instance* qat_crypto_get_instance_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_dh_init_tfm(struct crypto_kpp *tfm)
{
	struct qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	struct qat_crypto_instance *inst =
			qat_crypto_get_instance_node(get_current_node());

	if (!inst)
		return -EINVAL;

	ctx->p_size = 0;
	ctx->g2 = false;
	ctx->inst = inst;
	return 0;
}