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
struct ssh_hmac_ctx {int /*<<< orphan*/  digest; } ;

/* Variables and functions */
 int ssh_digest_update (int /*<<< orphan*/ ,void const*,size_t) ; 

int
ssh_hmac_update(struct ssh_hmac_ctx *ctx, const void *m, size_t mlen)
{
	return ssh_digest_update(ctx->digest, m, mlen);
}