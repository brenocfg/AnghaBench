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
struct skcipher_instance {int dummy; } ;
struct adiantum_instance_ctx {int /*<<< orphan*/  hash_spawn; int /*<<< orphan*/  blockcipher_spawn; int /*<<< orphan*/  streamcipher_spawn; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_drop_shash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_drop_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_drop_spawn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct skcipher_instance*) ; 
 struct adiantum_instance_ctx* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static void adiantum_free_instance(struct skcipher_instance *inst)
{
	struct adiantum_instance_ctx *ictx = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(&ictx->streamcipher_spawn);
	crypto_drop_spawn(&ictx->blockcipher_spawn);
	crypto_drop_shash(&ictx->hash_spawn);
	kfree(inst);
}