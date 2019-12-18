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
struct TYPE_2__ {int /*<<< orphan*/  aead_spawn; } ;
struct essiv_instance_ctx {TYPE_1__ u; } ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 struct essiv_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 int /*<<< orphan*/  crypto_drop_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aead_instance*) ; 

__attribute__((used)) static void essiv_aead_free_instance(struct aead_instance *inst)
{
	struct essiv_instance_ctx *ictx = aead_instance_ctx(inst);

	crypto_drop_aead(&ictx->u.aead_spawn);
	kfree(inst);
}