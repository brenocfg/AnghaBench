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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_hash {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

void crypto_hash_update(struct crypto_hash *ctx, const u8 *data, size_t len)
{
	if (ctx == NULL)
		return;
	HMAC_Update(ctx->ctx, data, len);
}