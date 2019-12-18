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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct mlx5_flow_namespace {TYPE_1__ base; } ;
struct fs_prio {int /*<<< orphan*/  objs; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_flow_namespace* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fs_add_node (TYPE_1__*,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  fs_init_namespace (struct mlx5_flow_namespace*) ; 
 struct mlx5_flow_namespace* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_flow_namespace *fs_create_namespace(struct fs_prio *prio,
						       const char *name)
{
	struct mlx5_flow_namespace	*ns;

	ns = kzalloc(sizeof(*ns), GFP_KERNEL);
	if (!ns)
		return ERR_PTR(-ENOMEM);

	fs_init_namespace(ns);
	fs_add_node(&ns->base, &prio->base, name, 1);
	list_add_tail(&ns->base.list, &prio->objs);

	return ns;
}