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
struct TYPE_4__ {int /*<<< orphan*/  rate; int /*<<< orphan*/  npartial; int /*<<< orphan*/  partial; } ;
typedef  TYPE_1__ cf_sha3_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cf_blockwise_acc_pad (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sha3_block ; 

__attribute__((used)) static void pad(cf_sha3_context *ctx, uint8_t domain, size_t npad)
{
  assert(npad >= 1);

  cf_blockwise_acc_pad(ctx->partial, &ctx->npartial, ctx->rate,
                       domain, 0x00, 0x80,
                       npad,
                       sha3_block, ctx);
}