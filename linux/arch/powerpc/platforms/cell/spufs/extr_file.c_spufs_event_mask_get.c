#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/ * slot; } ;
struct spu_lscsa {TYPE_2__ event_mask; } ;
struct TYPE_3__ {struct spu_lscsa* lscsa; } ;
struct spu_context {TYPE_1__ csa; } ;

/* Variables and functions */

__attribute__((used)) static u64 spufs_event_mask_get(struct spu_context *ctx)
{
	struct spu_lscsa *lscsa = ctx->csa.lscsa;
	return lscsa->event_mask.slot[0];
}