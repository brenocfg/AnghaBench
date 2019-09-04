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
typedef  int /*<<< orphan*/  (* cf_blockwise_out_fn ) (void*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  xor_bb (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 

void cf_blockwise_xor(uint8_t *partial, size_t *npartial, size_t nblock,
                      const void *inp, void *outp, size_t nbytes,
                      cf_blockwise_out_fn process, void *ctx)
{
  const uint8_t *inb = inp;
  uint8_t *outb = outp;

  assert(partial && *npartial < nblock);
  assert(inp || !nbytes);
  assert(process && ctx);

  while (nbytes)
  {
    /* If we're out of material, and need more, produce a block. */
    if (*npartial == 0)
    {
      process(ctx, partial);
      *npartial = nblock;
    }

    size_t offset = nblock - *npartial;
    size_t taken = MIN(*npartial, nbytes);
    xor_bb(outb, inb, partial + offset, taken);
    *npartial -= taken;
    nbytes -= taken;
    outb += taken;
    inb += taken;
  }
}