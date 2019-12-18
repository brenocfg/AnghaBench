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
struct skcipher_instance {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  skcipher_spawn; } ;
struct essiv_instance_ctx {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_drop_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct skcipher_instance*) ; 
 struct essiv_instance_ctx* skcipher_instance_ctx (struct skcipher_instance*) ; 

__attribute__((used)) static void essiv_skcipher_free_instance(struct skcipher_instance *inst)
{
	struct essiv_instance_ctx *ictx = skcipher_instance_ctx(inst);

	crypto_drop_skcipher(&ictx->u.skcipher_spawn);
	kfree(inst);
}