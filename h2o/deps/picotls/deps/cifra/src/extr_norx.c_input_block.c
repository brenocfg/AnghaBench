#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ blockctx ;

/* Variables and functions */
 int /*<<< orphan*/  input_block_final (void*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  switch_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_block(void *vctx, const uint8_t *data)
{
  /* Process block, then prepare for the next one. */
  blockctx *bctx = vctx;
  input_block_final(vctx, data);
  switch_domain(bctx->ctx, bctx->type);
}