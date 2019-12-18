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
struct mlx5_flow_rule {TYPE_1__ base; int /*<<< orphan*/  dest_attr; } ;
struct fs_fte {int /*<<< orphan*/  dests; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_to_add_rule_notifiers (struct mlx5_flow_rule*,struct fs_fte*) ; 
 int /*<<< orphan*/  fs_add_node (TYPE_1__*,int /*<<< orphan*/ *,char*,int) ; 
 char* get_dest_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_rule_to_tree(struct mlx5_flow_rule *rule,
			     struct fs_fte *fte)
{
	char *dest_name;

	dest_name = get_dest_name(&rule->dest_attr);
	fs_add_node(&rule->base, &fte->base, dest_name, 1);
	/* re-add to list, since fs_add_node reset our list */
	list_add_tail(&rule->base.list, &fte->dests);
	kfree(dest_name);
	call_to_add_rule_notifiers(rule, fte);
}