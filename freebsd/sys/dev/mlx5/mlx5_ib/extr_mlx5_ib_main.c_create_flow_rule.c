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
union ib_flow_spec {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_flow_prio {struct mlx5_flow_table* flow_table; int /*<<< orphan*/  refcount; } ;
struct mlx5_ib_flow_handler {struct mlx5_ib_flow_prio* prio; int /*<<< orphan*/  rule; int /*<<< orphan*/  list; } ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  match_criteria_enable; } ;
struct mlx5_flow_destination {int dummy; } ;
struct ib_flow_attr {unsigned int num_of_specs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct mlx5_ib_flow_handler* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO ; 
 int /*<<< orphan*/  MLX5_FS_DEFAULT_FLOW_TAG ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_match_criteria_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_attr (struct ib_flow_attr const*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_handler*) ; 
 int /*<<< orphan*/  kvfree (struct mlx5_flow_spec*) ; 
 struct mlx5_ib_flow_handler* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_add_flow_rule (struct mlx5_flow_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_flow_destination*) ; 
 struct mlx5_flow_spec* mlx5_vzalloc (int) ; 
 int parse_flow_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static struct mlx5_ib_flow_handler *create_flow_rule(struct mlx5_ib_dev *dev,
						     struct mlx5_ib_flow_prio *ft_prio,
						     const struct ib_flow_attr *flow_attr,
						     struct mlx5_flow_destination *dst)
{
	struct mlx5_flow_table	*ft = ft_prio->flow_table;
	struct mlx5_ib_flow_handler *handler;
	struct mlx5_flow_spec *spec;
	const void *ib_flow = (const void *)flow_attr + sizeof(*flow_attr);
	unsigned int spec_index;
	u32 action;
	int err = 0;

	if (!is_valid_attr(flow_attr))
		return ERR_PTR(-EINVAL);

	spec = mlx5_vzalloc(sizeof(*spec));
	handler = kzalloc(sizeof(*handler), GFP_KERNEL);
	if (!handler || !spec) {
		err = -ENOMEM;
		goto free;
	}

	INIT_LIST_HEAD(&handler->list);

	for (spec_index = 0; spec_index < flow_attr->num_of_specs; spec_index++) {
		err = parse_flow_attr(spec->match_criteria,
				      spec->match_value, ib_flow);
		if (err < 0)
			goto free;

		ib_flow += ((union ib_flow_spec *)ib_flow)->size;
	}

	spec->match_criteria_enable = get_match_criteria_enable(spec->match_criteria);
	action = dst ? MLX5_FLOW_CONTEXT_ACTION_FWD_DEST :
		MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO;
	handler->rule = mlx5_add_flow_rule(ft, spec->match_criteria_enable,
					   spec->match_criteria,
					   spec->match_value,
					   action,
					   MLX5_FS_DEFAULT_FLOW_TAG,
					   dst);

	if (IS_ERR(handler->rule)) {
		err = PTR_ERR(handler->rule);
		goto free;
	}

	ft_prio->refcount++;
	handler->prio = ft_prio;

	ft_prio->flow_table = ft;
free:
	if (err)
		kfree(handler);
	kvfree(spec);
	return err ? ERR_PTR(err) : handler;
}