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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  P; } ;
struct TYPE_5__ {int finalised; TYPE_1__ cmac; } ;
typedef  TYPE_2__ cf_cmac_stream ;

/* Variables and functions */
 int /*<<< orphan*/  cmac_process_final (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmac_process_final_pad(void *vctx, const uint8_t *block)
{
  cf_cmac_stream *ctx = vctx;
  cmac_process_final(ctx, block, ctx->cmac.P);
  ctx->finalised = 1;
}