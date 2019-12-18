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
struct cryptd_skcipher_ctx {int /*<<< orphan*/  refcnt; } ;
struct cryptd_skcipher {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct cryptd_skcipher_ctx* crypto_skcipher_ctx (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

bool cryptd_skcipher_queued(struct cryptd_skcipher *tfm)
{
	struct cryptd_skcipher_ctx *ctx = crypto_skcipher_ctx(&tfm->base);

	return refcount_read(&ctx->refcnt) - 1;
}