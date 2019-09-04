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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  (* cf_blockwise_in_fn ) (void*,int /*<<< orphan*/  const*) ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

void cf_blockwise_accumulate_final(uint8_t *partial, size_t *npartial, size_t nblock,
                                   const void *inp, size_t nbytes,
                                   cf_blockwise_in_fn process,
                                   cf_blockwise_in_fn process_final,
                                   void *ctx)
{
  const uint8_t *bufin = inp;
  assert(partial && *npartial < nblock);
  assert(inp || !nbytes);
  assert(process && ctx);

  /* If we have partial data, copy in to buffer. */
  if (*npartial && nbytes)
  {
    size_t space = nblock - *npartial;
    size_t taken = MIN(space, nbytes);

    memcpy(partial + *npartial, bufin, taken);

    bufin += taken;
    nbytes -= taken;
    *npartial += taken;

    /* If that gives us a full block, process it. */
    if (*npartial == nblock)
    {
      if (nbytes == 0)
        process_final(ctx, partial);
      else
        process(ctx, partial);
      *npartial = 0;
    }
  }

  /* now nbytes < nblock or *npartial == 0. */

  /* If we have a full block of data, process it directly. */
  while (nbytes >= nblock)
  {
    /* Partial buffer must be empty, or we're ignoring extant data */
    assert(*npartial == 0);

    if (nbytes == nblock)
      process_final(ctx, bufin);
    else
      process(ctx, bufin);
    bufin += nblock;
    nbytes -= nblock;
  }

  /* Finally, if we have remaining data, buffer it. */
  while (nbytes)
  {
    size_t space = nblock - *npartial;
    size_t taken = MIN(space, nbytes);

    memcpy(partial + *npartial, bufin, taken);

    bufin += taken;
    nbytes -= taken;
    *npartial += taken;

    /* If we started with *npartial, we must have copied it
     * in first. */
    assert(*npartial < nblock);
  }
}