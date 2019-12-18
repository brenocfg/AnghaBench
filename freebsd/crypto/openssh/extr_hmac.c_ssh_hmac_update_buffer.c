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
struct sshbuf {int dummy; } ;
struct ssh_hmac_ctx {int /*<<< orphan*/  digest; } ;

/* Variables and functions */
 int ssh_digest_update_buffer (int /*<<< orphan*/ ,struct sshbuf const*) ; 

int
ssh_hmac_update_buffer(struct ssh_hmac_ctx *ctx, const struct sshbuf *b)
{
	return ssh_digest_update_buffer(ctx->digest, b);
}