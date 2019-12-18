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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_flow_group {int dummy; } ;
struct list_head {int dummy; } ;
struct fs_fte {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fs_fte*) ; 
 struct fs_fte* fs_alloc_fte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fs_get_free_fg_index (struct mlx5_flow_group*,struct list_head**) ; 

__attribute__((used)) static struct fs_fte *fs_create_fte(struct mlx5_flow_group *fg,
			     u32 *match_value,
			     u8 action,
			     u32 flow_tag,
			     struct list_head **prev)
{
	struct fs_fte *fte;
	int index = 0;

	index = fs_get_free_fg_index(fg, prev);
	fte = fs_alloc_fte(action, flow_tag, match_value, index);
	if (IS_ERR(fte))
		return fte;

	return fte;
}