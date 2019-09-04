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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  npartial; int /*<<< orphan*/  partial; } ;
typedef  TYPE_1__ cf_poly1305 ;

/* Variables and functions */
 int /*<<< orphan*/  cf_blockwise_accumulate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  poly1305_whole_block ; 

void cf_poly1305_update(cf_poly1305 *ctx,
                        const uint8_t *buf,
                        size_t nbytes)
{
  cf_blockwise_accumulate(ctx->partial, &ctx->npartial,
                          sizeof ctx->partial,
                          buf, nbytes,
                          poly1305_whole_block,
                          ctx);
}