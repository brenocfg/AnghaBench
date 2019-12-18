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
struct pseudo_fs_context {int /*<<< orphan*/ * dops; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUF_MAGIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_buf_dentry_ops ; 
 struct pseudo_fs_context* init_pseudo (struct fs_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dma_buf_fs_init_context(struct fs_context *fc)
{
	struct pseudo_fs_context *ctx;

	ctx = init_pseudo(fc, DMA_BUF_MAGIC);
	if (!ctx)
		return -ENOMEM;
	ctx->dops = &dma_buf_dentry_ops;
	return 0;
}