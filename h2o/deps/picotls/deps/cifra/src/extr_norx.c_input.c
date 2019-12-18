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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  partial ;
typedef  int /*<<< orphan*/  norx32_ctx ;
struct TYPE_4__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ blockctx ;

/* Variables and functions */
 int RATE_BYTES ; 
 int /*<<< orphan*/  cf_blockwise_accumulate (int*,size_t*,int,int const*,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  input_block ; 
 int /*<<< orphan*/  input_block_final (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void input(norx32_ctx *ctx, uint32_t type,
                  const uint8_t *buf, size_t nbuf)
{
  uint8_t partial[RATE_BYTES];
  size_t npartial = 0;
  blockctx bctx = { ctx, type };

  /* Process input. */
  cf_blockwise_accumulate(partial, &npartial, sizeof partial,
                          buf, nbuf,
                          input_block,
                          &bctx);

  /* Now pad partial. This contains the trailing portion of buf. */
  memset(partial + npartial, 0, sizeof(partial) - npartial);
  partial[npartial] = 0x01;
  partial[sizeof(partial) - 1] ^= 0x80;

  input_block_final(&bctx, partial);
}