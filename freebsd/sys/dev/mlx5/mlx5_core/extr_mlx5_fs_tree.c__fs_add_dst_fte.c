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
struct mlx5_flow_table {int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  vport; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;
struct mlx5_flow_rule {TYPE_1__ base; int /*<<< orphan*/  clients_lock; int /*<<< orphan*/  clients_data; int /*<<< orphan*/  dest_attr; } ;
struct mlx5_flow_group {int /*<<< orphan*/  id; } ;
struct mlx5_flow_destination {int dummy; } ;
struct fs_fte {int /*<<< orphan*/  dests_size; int /*<<< orphan*/  dests; int /*<<< orphan*/  action; int /*<<< orphan*/  flow_tag; int /*<<< orphan*/  index; int /*<<< orphan*/  val; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlx5_flow_rule* ERR_PTR (int) ; 
 int /*<<< orphan*/  FS_TYPE_FLOW_DEST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_get_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_get_parent (struct mlx5_flow_table*,struct mlx5_flow_group*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_rule*) ; 
 struct mlx5_flow_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx5_flow_destination*,int) ; 
 int mlx5_cmd_fs_set_fte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_rule *_fs_add_dst_fte(struct fs_fte *fte,
					      struct mlx5_flow_group *fg,
					      struct mlx5_flow_destination *dest)
{
	struct mlx5_flow_table *ft;
	struct mlx5_flow_rule *dst;
	int err;

	dst = kzalloc(sizeof(*dst), GFP_KERNEL);
	if (!dst)
		return ERR_PTR(-ENOMEM);

	memcpy(&dst->dest_attr, dest, sizeof(*dest));
	dst->base.type = FS_TYPE_FLOW_DEST;
	INIT_LIST_HEAD(&dst->clients_data);
	mutex_init(&dst->clients_lock);
	fs_get_parent(ft, fg);
	/*Add dest to dests list- added as first element after the head*/
	list_add_tail(&dst->base.list, &fte->dests);
	fte->dests_size++;
	err = mlx5_cmd_fs_set_fte(fs_get_dev(&ft->base),
				  ft->vport,
				  &fte->status,
				  fte->val, ft->type,
				  ft->id, fte->index, fg->id, fte->flow_tag,
				  fte->action, fte->dests_size, &fte->dests);
	if (err)
		goto free_dst;

	list_del(&dst->base.list);

	return dst;

free_dst:
	list_del(&dst->base.list);
	kfree(dst);
	fte->dests_size--;
	return ERR_PTR(err);
}