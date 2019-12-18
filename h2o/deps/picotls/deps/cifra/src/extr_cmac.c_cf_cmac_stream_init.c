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
typedef  int /*<<< orphan*/  cf_prp ;
struct TYPE_4__ {int /*<<< orphan*/  cmac; } ;
typedef  TYPE_1__ cf_cmac_stream ;

/* Variables and functions */
 int /*<<< orphan*/  cf_cmac_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/  cf_cmac_stream_reset (TYPE_1__*) ; 

void cf_cmac_stream_init(cf_cmac_stream *ctx, const cf_prp *prp, void *prpctx)
{
  cf_cmac_init(&ctx->cmac, prp, prpctx);
  cf_cmac_stream_reset(ctx);
}