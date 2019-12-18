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
struct mlx5_flow_namespace {int /*<<< orphan*/  notifiers_rw_sem; int /*<<< orphan*/  list_notifiers; } ;
struct mlx5_flow_handler {int /*<<< orphan*/  list; struct mlx5_flow_namespace* ns; void* client_context; void* del_dst_cb; void* add_dst_cb; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  void* rule_event_fn ;
typedef  enum mlx5_flow_namespace_type { ____Placeholder_mlx5_flow_namespace_type } mlx5_flow_namespace_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_flow_handler* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct mlx5_flow_handler* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_flow_namespace* mlx5_get_flow_namespace (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct mlx5_flow_handler *mlx5_register_rule_notifier(struct mlx5_core_dev *dev,
								enum mlx5_flow_namespace_type ns_type,
								rule_event_fn add_cb,
								rule_event_fn del_cb,
								void *context)
{
	struct mlx5_flow_namespace *ns;
	struct mlx5_flow_handler *handler;

	ns = mlx5_get_flow_namespace(dev, ns_type);
	if (!ns)
		return ERR_PTR(-EINVAL);

	handler = kzalloc(sizeof(*handler), GFP_KERNEL);
	if (!handler)
		return ERR_PTR(-ENOMEM);

	handler->add_dst_cb = add_cb;
	handler->del_dst_cb = del_cb;
	handler->client_context = context;
	handler->ns = ns;
	down_write(&ns->notifiers_rw_sem);
	list_add_tail(&handler->list, &ns->list_notifiers);
	up_write(&ns->notifiers_rw_sem);

	return handler;
}