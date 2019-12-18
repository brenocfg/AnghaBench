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
struct padlock_sha_ctx {scalar_t__ psc_size; scalar_t__ psc_offset; int /*<<< orphan*/ * psc_buf; } ;

/* Variables and functions */

__attribute__((used)) static void
padlock_sha_init(struct padlock_sha_ctx *ctx)
{

	ctx->psc_buf = NULL;
	ctx->psc_offset = 0;
	ctx->psc_size = 0;
}