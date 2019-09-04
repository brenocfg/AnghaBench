#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t counter_offset; size_t counter_width; TYPE_1__* prp; } ;
typedef  TYPE_2__ cf_ctr ;
struct TYPE_4__ {size_t blocksz; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void cf_ctr_custom_counter(cf_ctr *ctx, size_t offset, size_t width)
{
  assert(ctx->prp->blocksz <= offset + width);
  ctx->counter_offset = offset;
  ctx->counter_width = width;
}