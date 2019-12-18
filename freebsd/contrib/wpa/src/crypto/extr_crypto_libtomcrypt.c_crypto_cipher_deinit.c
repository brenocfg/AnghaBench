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
struct TYPE_2__ {int /*<<< orphan*/  cbc; } ;
struct crypto_cipher {TYPE_1__ u; int /*<<< orphan*/  rc4; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbc_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct crypto_cipher*) ; 

void crypto_cipher_deinit(struct crypto_cipher *ctx)
{
	if (!ctx->rc4)
		cbc_done(&ctx->u.cbc);
	os_free(ctx);
}