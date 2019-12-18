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
struct mlx5_cmd_work_ent {int uin_size; int uout_size; int page_queue; struct mlx5_cmd* cmd; void* context; scalar_t__ callback; void* uout; struct mlx5_cmd_msg* out; struct mlx5_cmd_msg* in; } ;
struct mlx5_cmd_msg {int dummy; } ;
struct mlx5_cmd {int dummy; } ;
typedef  scalar_t__ mlx5_cmd_cbk_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_cmd_work_ent* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlx5_cmd_work_ent* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_cmd_work_ent *alloc_cmd(struct mlx5_cmd *cmd,
					   struct mlx5_cmd_msg *in,
					   int uin_size,
					   struct mlx5_cmd_msg *out,
					   void *uout, int uout_size,
					   mlx5_cmd_cbk_t cbk,
					   void *context, int page_queue)
{
	gfp_t alloc_flags = cbk ? GFP_ATOMIC : GFP_KERNEL;
	struct mlx5_cmd_work_ent *ent;

	ent = kzalloc(sizeof(*ent), alloc_flags);
	if (!ent)
		return ERR_PTR(-ENOMEM);

	ent->in		= in;
	ent->uin_size	= uin_size;
	ent->out	= out;
	ent->uout	= uout;
	ent->uout_size	= uout_size;
	ent->callback	= cbk;
	ent->context	= context;
	ent->cmd	= cmd;
	ent->page_queue = page_queue;

	return ent;
}