#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ rate; scalar_t__ npartial; } ;
typedef  TYPE_1__ cf_sha3_context ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_HASH_PAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mem_clean (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pad (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  squeeze (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void pad_and_squeeze(cf_sha3_context *ctx, uint8_t *out, size_t nout)
{
  pad(ctx, DOMAIN_HASH_PAD, ctx->rate - ctx->npartial);
  assert(ctx->npartial == 0);

  squeeze(ctx, out, nout);
  mem_clean(ctx, sizeof *ctx);
}