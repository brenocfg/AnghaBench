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
struct spu_context {TYPE_1__* ops; int /*<<< orphan*/  tagwait; } ;
struct mfc_dma_command {int dummy; } ;
struct TYPE_2__ {int (* send_mfc_command ) (struct spu_context*,struct mfc_dma_command*) ;int /*<<< orphan*/  (* set_mfc_query ) (struct spu_context*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int stub1 (struct spu_context*,struct mfc_dma_command*) ; 
 int /*<<< orphan*/  stub2 (struct spu_context*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct spu_context*,struct mfc_dma_command*) ; 

__attribute__((used)) static int spu_send_mfc_command(struct spu_context *ctx,
				struct mfc_dma_command cmd,
				int *error)
{
	*error = ctx->ops->send_mfc_command(ctx, &cmd);
	if (*error == -EAGAIN) {
		/* wait for any tag group to complete
		   so we have space for the new command */
		ctx->ops->set_mfc_query(ctx, ctx->tagwait, 1);
		/* try again, because the queue might be
		   empty again */
		*error = ctx->ops->send_mfc_command(ctx, &cmd);
		if (*error == -EAGAIN)
			return 0;
	}
	return 1;
}