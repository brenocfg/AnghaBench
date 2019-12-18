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
typedef  int /*<<< orphan*/  uint8_t ;
struct hmac_ctx {int /*<<< orphan*/  innerctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void
g_eli_crypto_hmac_update(struct hmac_ctx *ctx, const uint8_t *data,
    size_t datasize)
{

	SHA512_Update(&ctx->innerctx, data, datasize);
}