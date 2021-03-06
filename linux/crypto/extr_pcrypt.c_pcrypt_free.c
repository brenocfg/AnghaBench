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
struct pcrypt_instance_ctx {int /*<<< orphan*/  spawn; } ;
struct aead_instance {int dummy; } ;

/* Variables and functions */
 struct pcrypt_instance_ctx* aead_instance_ctx (struct aead_instance*) ; 
 int /*<<< orphan*/  crypto_drop_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aead_instance*) ; 

__attribute__((used)) static void pcrypt_free(struct aead_instance *inst)
{
	struct pcrypt_instance_ctx *ctx = aead_instance_ctx(inst);

	crypto_drop_aead(&ctx->spawn);
	kfree(inst);
}