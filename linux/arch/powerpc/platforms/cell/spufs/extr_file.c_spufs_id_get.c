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
typedef  unsigned int u64 ;
struct spu_context {scalar_t__ state; TYPE_1__* spu; } ;
struct TYPE_2__ {unsigned int number; } ;

/* Variables and functions */
 scalar_t__ SPU_STATE_RUNNABLE ; 

__attribute__((used)) static u64 spufs_id_get(struct spu_context *ctx)
{
	u64 num;

	if (ctx->state == SPU_STATE_RUNNABLE)
		num = ctx->spu->number;
	else
		num = (unsigned int)-1;

	return num;
}