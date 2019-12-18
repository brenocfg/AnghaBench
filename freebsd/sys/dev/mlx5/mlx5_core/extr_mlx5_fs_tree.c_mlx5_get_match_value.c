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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct fs_base* parent; } ;
struct mlx5_flow_rule {TYPE_1__ base; } ;
struct fs_fte {int /*<<< orphan*/  val; } ;
struct fs_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fs_get_obj (struct fs_fte*,struct fs_base*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void mlx5_get_match_value(u32 *match_value,
			  struct mlx5_flow_rule *rule)
{
	struct fs_base *pbase;
	struct fs_fte *fte;

	pbase = rule->base.parent;
	WARN_ON(!pbase);
	fs_get_obj(fte, pbase);

	memcpy(match_value, fte->val, sizeof(fte->val));
}