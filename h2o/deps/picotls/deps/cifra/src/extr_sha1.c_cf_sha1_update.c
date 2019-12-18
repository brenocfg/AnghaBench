#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  npartial; int /*<<< orphan*/  partial; } ;
typedef  TYPE_1__ cf_sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  cf_blockwise_accumulate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void const*,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sha1_update_block ; 

void cf_sha1_update(cf_sha1_context *ctx, const void *data, size_t nbytes)
{
  cf_blockwise_accumulate(ctx->partial, &ctx->npartial, sizeof ctx->partial,
                          data, nbytes,
                          sha1_update_block, ctx);
}