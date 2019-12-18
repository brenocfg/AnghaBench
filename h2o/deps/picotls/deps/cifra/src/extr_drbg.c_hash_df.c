#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  cf_chash_ctx ;
struct TYPE_3__ {int /*<<< orphan*/  hashsz; int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,void const*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  write32_be (size_t,int*) ; 

__attribute__((used)) static void hash_df(const cf_chash *H,
                    const void *in1, size_t nin1,
                    const void *in2, size_t nin2,
                    const void *in3, size_t nin3,
                    const void *in4, size_t nin4,
                    uint8_t *out, size_t nout)
{
  uint8_t counter = 1;
  uint32_t bits_to_return = nout * 8;
  uint8_t cbuf[4];
  uint8_t block[CF_MAXHASH];

  write32_be(bits_to_return, cbuf);

  while (nout)
  {
    /* Make a block.  This is the hash of:
     *   counter || bits_to_return || in1 || in2 || in3 | in4
     */
    cf_chash_ctx ctx;
    H->init(&ctx);
    H->update(&ctx, &counter, sizeof counter);
    H->update(&ctx, cbuf, sizeof cbuf);
    H->update(&ctx, in1, nin1);
    H->update(&ctx, in2, nin2);
    H->update(&ctx, in3, nin3);
    H->update(&ctx, in4, nin4);
    H->digest(&ctx, block);

    size_t take = MIN(H->hashsz, nout);
    memcpy(out, block, take);
    out += take;
    nout -= take;

    counter += 1;
  }
}