#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  partial ;
struct TYPE_9__ {int /*<<< orphan*/  sum; int /*<<< orphan*/  offset; int /*<<< orphan*/  o; TYPE_3__* member_0; } ;
typedef  TYPE_2__ ocb_hash ;
struct TYPE_10__ {int /*<<< orphan*/  L_star; TYPE_1__* prp; } ;
typedef  TYPE_3__ ocb ;
struct TYPE_8__ {int /*<<< orphan*/  blocksz; } ;

/* Variables and functions */
 int BLOCK ; 
 int /*<<< orphan*/  cf_blockwise_accumulate (int*,size_t*,int /*<<< orphan*/ ,int const*,size_t,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  cf_gf128_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_tobytes_be (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mem_clean (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocb_hash_block ; 
 int /*<<< orphan*/  ocb_hash_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ocb_hash_sum (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocb_process_header(ocb *o, const uint8_t *header, size_t nheader,
                               uint8_t out[BLOCK])
{
  ocb_hash ctx = { o };
  ocb_hash_init(&ctx);

  uint8_t partial[BLOCK];
  size_t npartial = 0;

  cf_blockwise_accumulate(partial, &npartial,
                          o->prp->blocksz,
                          header, nheader,
                          ocb_hash_block,
                          &ctx);

  if (npartial)
  {
    /* Offset_* = Offset_m xor L_* */
    cf_gf128_add(ctx.offset, o->L_star, ctx.offset);

    /* CipherInput = (A_* || 1 || zeros(127 - bitlen(A_*))) xor Offset_* */
    memset(partial + npartial, 0, sizeof(partial) - npartial);
    partial[npartial] = 0x80;

    /* Sum = Sum_m xor ENCIPHER(K, CipherInput) */
    ocb_hash_sum(ctx.o, partial, ctx.sum, ctx.offset);
  }

  cf_gf128_tobytes_be(ctx.sum, out);
  mem_clean(&ctx, sizeof ctx);
}