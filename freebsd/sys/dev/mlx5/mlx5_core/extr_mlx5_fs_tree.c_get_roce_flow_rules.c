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
typedef  int u8 ;
struct mlx5_flow_rules_list {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MLX5_ROCE_VERSION_1_CAP ; 
 int MLX5_ROCE_VERSION_2_CAP ; 
 struct mlx5_flow_rules_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules_list (struct mlx5_flow_rules_list*) ; 
 int set_rocev1_rules (int /*<<< orphan*/ *) ; 
 int set_rocev2_rules (int /*<<< orphan*/ *) ; 

struct mlx5_flow_rules_list *get_roce_flow_rules(u8 roce_mode)
{
	int err = 0;
	struct mlx5_flow_rules_list *rules_list =
		kzalloc(sizeof(*rules_list), GFP_KERNEL);

	if (!rules_list)
		return NULL;

	INIT_LIST_HEAD(&rules_list->head);

	if (roce_mode & MLX5_ROCE_VERSION_1_CAP) {
		err = set_rocev1_rules(&rules_list->head);
		if (err)
			goto free_list;
	}
	if (roce_mode & MLX5_ROCE_VERSION_2_CAP)
		err = set_rocev2_rules(&rules_list->head);
	if (err)
		goto free_list;

	return rules_list;

free_list:
	mlx5_del_flow_rules_list(rules_list);
	return NULL;
}