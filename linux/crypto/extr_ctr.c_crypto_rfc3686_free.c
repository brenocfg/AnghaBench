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
struct crypto_skcipher_spawn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_drop_skcipher (struct crypto_skcipher_spawn*) ; 
 int /*<<< orphan*/  kfree (struct skcipher_instance*) ; 
 struct crypto_skcipher_spawn* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static void crypto_rfc3686_free(struct skcipher_instance *inst)
{
	struct crypto_skcipher_spawn *spawn = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(spawn);
	kfree(inst);
}