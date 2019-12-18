#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/ ** attrs; } ;
struct sensor_group {TYPE_2__ sg; TYPE_4__* sgattrs; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_9__ {TYPE_1__ attr; } ;
struct TYPE_8__ {scalar_t__ opal_no; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  add_attr (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/  const) ; 
 TYPE_3__* ops_info ; 
 int /*<<< orphan*/  sg_kobj ; 
 int sysfs_create_group (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int add_attr_group(const __be32 *ops, int len, struct sensor_group *sg,
			   u32 handle)
{
	int i, j;
	int count = 0;

	for (i = 0; i < len; i++)
		for (j = 0; j < ARRAY_SIZE(ops_info); j++)
			if (be32_to_cpu(ops[i]) == ops_info[j].opal_no) {
				add_attr(handle, &sg->sgattrs[count], j);
				sg->sg.attrs[count] =
					&sg->sgattrs[count].attr.attr;
				count++;
			}

	return sysfs_create_group(sg_kobj, &sg->sg);
}