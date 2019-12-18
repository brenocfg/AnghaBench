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
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;
struct genl_info {struct nlattr** attrs; } ;
typedef  enum mt753x_attr { ____Placeholder_mt753x_attr } mt753x_attr ;

/* Variables and functions */
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int mt753x_nl_get_u32(struct genl_info *info, enum mt753x_attr attr,
			     u32 *val)
{
	struct nlattr *na;

	na = info->attrs[attr];
	if (na) {
		*val = nla_get_u32(na);
		return 0;
	}

	return -1;
}