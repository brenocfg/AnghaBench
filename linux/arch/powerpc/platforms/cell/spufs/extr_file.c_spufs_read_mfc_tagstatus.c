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
typedef  int u32 ;
struct spu_context {int tagwait; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* read_mfc_tagstatus ) (struct spu_context*) ;int /*<<< orphan*/  (* set_mfc_query ) (struct spu_context*,int,int) ;} ;

/* Variables and functions */
 int stub1 (struct spu_context*) ; 
 int /*<<< orphan*/  stub2 (struct spu_context*,int,int) ; 

__attribute__((used)) static int spufs_read_mfc_tagstatus(struct spu_context *ctx, u32 *status)
{
	/* See if there is one tag group is complete */
	/* FIXME we need locking around tagwait */
	*status = ctx->ops->read_mfc_tagstatus(ctx) & ctx->tagwait;
	ctx->tagwait &= ~*status;
	if (*status)
		return 1;

	/* enable interrupt waiting for any tag group,
	   may silently fail if interrupts are already enabled */
	ctx->ops->set_mfc_query(ctx, ctx->tagwait, 1);
	return 0;
}