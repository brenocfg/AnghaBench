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
struct crypto_aead_spawn {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cryptd_aead_request_ctx {int dummy; } ;
struct cryptd_aead_ctx {struct crypto_aead* child; } ;
struct aead_instance_ctx {struct crypto_aead_spawn aead_spawn; } ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int PTR_ERR (struct crypto_aead*) ; 
 struct aead_instance* aead_alg_instance (struct crypto_aead*) ; 
 struct aead_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 struct cryptd_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_reqsize (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_reqsize (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 struct crypto_aead* crypto_spawn_aead (struct crypto_aead_spawn*) ; 
 int /*<<< orphan*/  max (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cryptd_aead_init_tfm(struct crypto_aead *tfm)
{
	struct aead_instance *inst = aead_alg_instance(tfm);
	struct aead_instance_ctx *ictx = aead_instance_ctx(inst);
	struct crypto_aead_spawn *spawn = &ictx->aead_spawn;
	struct cryptd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_aead *cipher;

	cipher = crypto_spawn_aead(spawn);
	if (IS_ERR(cipher))
		return PTR_ERR(cipher);

	ctx->child = cipher;
	crypto_aead_set_reqsize(
		tfm, max((unsigned)sizeof(struct cryptd_aead_request_ctx),
			 crypto_aead_reqsize(cipher)));
	return 0;
}