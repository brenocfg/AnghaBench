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
struct mlx5_flow_root_namespace {struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
struct fs_base {int dummy; } ;

/* Variables and functions */
 struct mlx5_flow_root_namespace* find_root (struct fs_base*) ; 

__attribute__((used)) static inline struct mlx5_core_dev *fs_get_dev(struct fs_base *node)
{
	struct mlx5_flow_root_namespace *root = find_root(node);

	if (root)
		return root->dev;
	return NULL;
}