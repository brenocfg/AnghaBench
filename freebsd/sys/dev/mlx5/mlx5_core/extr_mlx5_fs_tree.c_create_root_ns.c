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
struct mlx5_flow_namespace {int /*<<< orphan*/  base; } ;
struct mlx5_flow_root_namespace {int table_type; struct mlx5_flow_namespace ns; int /*<<< orphan*/  fs_chain_lock; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum fs_ft_type { ____Placeholder_fs_ft_type } fs_ft_type ;

/* Variables and functions */
 int /*<<< orphan*/  fs_add_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fs_init_namespace (struct mlx5_flow_namespace*) ; 
 struct mlx5_flow_root_namespace* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_root_namespace *create_root_ns(struct mlx5_core_dev *dev,
							  enum fs_ft_type
							  table_type,
							  char *name)
{
	struct mlx5_flow_root_namespace *root_ns;
	struct mlx5_flow_namespace *ns;

	/* create the root namespace */
	root_ns = mlx5_vzalloc(sizeof(*root_ns));
	if (!root_ns)
		goto err;

	root_ns->dev = dev;
	root_ns->table_type = table_type;
	mutex_init(&root_ns->fs_chain_lock);

	ns = &root_ns->ns;
	fs_init_namespace(ns);
	fs_add_node(&ns->base, NULL, name, 1);

	return root_ns;
err:
	return NULL;
}