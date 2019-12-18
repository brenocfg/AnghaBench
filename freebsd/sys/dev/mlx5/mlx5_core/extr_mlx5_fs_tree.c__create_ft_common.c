#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  list; int /*<<< orphan*/  type; } ;
struct mlx5_flow_table {scalar_t__ type; int max_fte; int id; int /*<<< orphan*/  vport; TYPE_1__ base; scalar_t__ level; int /*<<< orphan*/  fgs; } ;
struct mlx5_flow_root_namespace {scalar_t__ table_type; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct mlx5_flow_namespace {TYPE_2__ base; } ;
struct mlx5_core_dev {int dummy; } ;
struct fs_prio {scalar_t__ num_ft; scalar_t__ max_ft; int /*<<< orphan*/  objs; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {int /*<<< orphan*/  modify_root; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct mlx5_flow_table* ERR_PTR (int) ; 
 scalar_t__ FS_FT_ESW_EGRESS_ACL ; 
 scalar_t__ FS_FT_ESW_INGRESS_ACL ; 
 scalar_t__ FS_FT_NIC_RX ; 
 int /*<<< orphan*/  FS_TYPE_FLOW_TABLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MLX5_CAP_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fs_add_node (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ alloc_new_level (struct fs_prio*) ; 
 int create_star_rule (struct mlx5_flow_table*,struct fs_prio*) ; 
 int /*<<< orphan*/  destroy_star_rule (struct mlx5_flow_table*,struct fs_prio*) ; 
 struct mlx5_flow_root_namespace* find_root (TYPE_2__*) ; 
 TYPE_3__ flow_table_properties_nic_receive ; 
 struct mlx5_core_dev* fs_get_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  fs_init_node (TYPE_1__*,int) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_table*) ; 
 struct mlx5_flow_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlx5_cmd_fs_create_ft (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  mlx5_cmd_fs_destroy_ft (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int update_root_ft_create (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*) ; 

__attribute__((used)) static struct mlx5_flow_table *_create_ft_common(struct mlx5_flow_namespace *ns,
						 u16 vport,
						 struct fs_prio *fs_prio,
						 int max_fte,
						 const char *name)
{
	struct mlx5_flow_table *ft;
	int err;
	int log_table_sz;
	int ft_size;
	char gen_name[20];
	struct mlx5_flow_root_namespace *root = find_root(&ns->base);
	struct mlx5_core_dev *dev = fs_get_dev(&ns->base);

	if (!root) {
		mlx5_core_err(dev,
		    "flow steering failed to find root of namespace %s",
		    ns->base.name);
		return ERR_PTR(-ENODEV);
	}

	if (fs_prio->num_ft == fs_prio->max_ft)
		return ERR_PTR(-ENOSPC);

	ft  = kzalloc(sizeof(*ft), GFP_KERNEL);
	if (!ft)
		return ERR_PTR(-ENOMEM);

	fs_init_node(&ft->base, 1);
	INIT_LIST_HEAD(&ft->fgs);

	/* Temporarily WA until we expose the level set in the API */
	if (root->table_type == FS_FT_ESW_EGRESS_ACL ||
		root->table_type == FS_FT_ESW_INGRESS_ACL)
		ft->level = 0;
	else
		ft->level = alloc_new_level(fs_prio);

	ft->base.type = FS_TYPE_FLOW_TABLE;
	ft->vport = vport;
	ft->type = root->table_type;
	/*Two entries are reserved for star rules*/
	ft_size = roundup_pow_of_two(max_fte + 2);
	/*User isn't aware to those rules*/
	ft->max_fte = ft_size - 2;
	log_table_sz = ilog2(ft_size);
	err = mlx5_cmd_fs_create_ft(root->dev, ft->vport, ft->type,
				    ft->level, log_table_sz, &ft->id);
	if (err)
		goto free_ft;

	err = create_star_rule(ft, fs_prio);
	if (err)
		goto del_ft;

	if ((root->table_type == FS_FT_NIC_RX) && MLX5_CAP_FLOWTABLE(root->dev,
			       flow_table_properties_nic_receive.modify_root)) {
		err = update_root_ft_create(root, ft);
		if (err)
			goto destroy_star_rule;
	}

	if (!name || !strlen(name)) {
		snprintf(gen_name, 20, "flow_table_%u", ft->id);
		_fs_add_node(&ft->base, gen_name, &fs_prio->base);
	} else {
		_fs_add_node(&ft->base, name, &fs_prio->base);
	}
	list_add_tail(&ft->base.list, &fs_prio->objs);
	fs_prio->num_ft++;

	return ft;

destroy_star_rule:
	destroy_star_rule(ft, fs_prio);
del_ft:
	mlx5_cmd_fs_destroy_ft(root->dev, ft->vport, ft->type, ft->id);
free_ft:
	kfree(ft);
	return ERR_PTR(err);
}