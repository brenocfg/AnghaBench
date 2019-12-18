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
struct padlock_sha_ctx {int /*<<< orphan*/  psc_offset; int /*<<< orphan*/  psc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  padlock_do_sha1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  padlock_sha_free (struct padlock_sha_ctx*) ; 

__attribute__((used)) static void
padlock_sha1_final(uint8_t *hash, struct padlock_sha_ctx *ctx)
{

	padlock_do_sha1(ctx->psc_buf, hash, ctx->psc_offset);
	padlock_sha_free(ctx);
}