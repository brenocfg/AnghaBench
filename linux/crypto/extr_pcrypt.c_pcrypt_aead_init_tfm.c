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
struct pcrypt_request {int dummy; } ;
struct pcrypt_instance_ctx {int /*<<< orphan*/  spawn; int /*<<< orphan*/  tfm_count; } ;
struct pcrypt_aead_ctx {struct crypto_aead* child; int /*<<< orphan*/  cb_cpu; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int PTR_ERR (struct crypto_aead*) ; 
 struct aead_instance* aead_alg_instance (struct crypto_aead*) ; 
 struct pcrypt_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int cpumask_weight (int /*<<< orphan*/ ) ; 
 struct pcrypt_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_reqsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,scalar_t__) ; 
 struct crypto_aead* crypto_spawn_aead (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcrypt_aead_init_tfm(struct crypto_aead *tfm)
{
	int cpu, cpu_index;
	struct aead_instance *inst = aead_alg_instance(tfm);
	struct pcrypt_instance_ctx *ictx = aead_instance_ctx(inst);
	struct pcrypt_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_aead *cipher;

	cpu_index = (unsigned int)atomic_inc_return(&ictx->tfm_count) %
		    cpumask_weight(cpu_online_mask);

	ctx->cb_cpu = cpumask_first(cpu_online_mask);
	for (cpu = 0; cpu < cpu_index; cpu++)
		ctx->cb_cpu = cpumask_next(ctx->cb_cpu, cpu_online_mask);

	cipher = crypto_spawn_aead(&ictx->spawn);

	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = cipher;
	crypto_aead_set_reqsize(tfm, sizeof(struct pcrypt_request) +
				     sizeof(struct aead_request) +
				     crypto_aead_reqsize(cipher));

	return 0;
}