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
struct fs_base {int dummy; } ;
struct mlx5_flow_namespace {struct fs_base base; } ;
struct mlx5_core_dev {int dummy; } ;
struct init_tree_node {scalar_t__ type; int min_ft_level; int ar_size; struct init_tree_node* children; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_ft; int /*<<< orphan*/  caps; } ;
struct fs_prio {struct fs_base base; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FS_TYPE_NAMESPACE ; 
 scalar_t__ FS_TYPE_PRIO ; 
 scalar_t__ IS_ERR (struct mlx5_flow_namespace*) ; 
 int PTR_ERR (struct mlx5_flow_namespace*) ; 
 struct mlx5_flow_namespace* fs_create_namespace (struct mlx5_flow_namespace*,int /*<<< orphan*/ ) ; 
 struct mlx5_flow_namespace* fs_create_prio (struct mlx5_flow_namespace*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_namespace*,struct fs_base*) ; 
 int /*<<< orphan*/  has_required_caps (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _init_root_tree(struct mlx5_core_dev *dev, int max_ft_level,
		    struct init_tree_node *node, struct fs_base *base_parent,
		    struct init_tree_node *tree_parent)
{
	struct mlx5_flow_namespace *fs_ns;
	struct fs_prio *fs_prio;
	int priority;
	struct fs_base *base;
	int i;
	int err = 0;

	if (node->type == FS_TYPE_PRIO) {
		if ((node->min_ft_level > max_ft_level) ||
		    !has_required_caps(dev, &node->caps))
			goto out;

		fs_get_obj(fs_ns, base_parent);
		priority = node - tree_parent->children;
		fs_prio = fs_create_prio(fs_ns, priority,
					 node->max_ft,
					 node->name, node->flags);
		if (IS_ERR(fs_prio)) {
			err = PTR_ERR(fs_prio);
			goto out;
		}
		base = &fs_prio->base;
	} else if (node->type == FS_TYPE_NAMESPACE) {
		fs_get_obj(fs_prio, base_parent);
		fs_ns = fs_create_namespace(fs_prio, node->name);
		if (IS_ERR(fs_ns)) {
			err = PTR_ERR(fs_ns);
			goto out;
		}
		base = &fs_ns->base;
	} else {
		return -EINVAL;
	}
	for (i = 0; i < node->ar_size; i++) {
		err = _init_root_tree(dev, max_ft_level, &node->children[i], base,
				      node);
		if (err)
			break;
	}
out:
	return err;
}