#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  rate; } ;
typedef  TYPE_1__ cf_sha3_context ;

/* Variables and functions */
 size_t MIN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  extract (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  permute (TYPE_1__*) ; 

__attribute__((used)) static void squeeze(cf_sha3_context *ctx, uint8_t *out, size_t nbytes)
{
  while (nbytes)
  {
    size_t take = MIN(nbytes, ctx->rate);
    extract(ctx, out, take);
    out += take;
    nbytes -= take;

    assert(nbytes == 0);
#if 0
    /* Note: if we ever have |H| >= rate, we need to permute
     * after each rate-length block.
     *
     * This cannot currently happen. */
    if (nbytes)
      permute(ctx);
#endif
  }
}