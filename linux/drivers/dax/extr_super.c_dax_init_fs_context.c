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
struct pseudo_fs_context {int /*<<< orphan*/ * ops; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAXFS_MAGIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dax_sops ; 
 struct pseudo_fs_context* init_pseudo (struct fs_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dax_init_fs_context(struct fs_context *fc)
{
	struct pseudo_fs_context *ctx = init_pseudo(fc, DAXFS_MAGIC);
	if (!ctx)
		return -ENOMEM;
	ctx->ops = &dax_sops;
	return 0;
}