#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {struct fs_base* parent; } ;
struct mlx5_flow_rule {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  match_criteria; } ;
struct mlx5_flow_group {TYPE_2__ mask; } ;
struct fs_base {struct fs_base* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_group*,struct fs_base*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void mlx5_get_match_criteria(u32 *match_criteria,
			     struct mlx5_flow_rule *rule)
{
	struct fs_base *pbase;
	struct mlx5_flow_group *fg;

	pbase = rule->base.parent;
	WARN_ON(!pbase);
	pbase = pbase->parent;
	WARN_ON(!pbase);

	fs_get_obj(fg, pbase);
	memcpy(match_criteria, &fg->mask.match_criteria,
	       sizeof(fg->mask.match_criteria));
}