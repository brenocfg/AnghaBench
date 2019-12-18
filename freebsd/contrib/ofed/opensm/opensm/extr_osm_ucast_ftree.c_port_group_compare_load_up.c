#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int counter_up; } ;
typedef  TYPE_1__ ftree_port_group_t ;

/* Variables and functions */
 int compare_port_groups_by_remote_switch_index (TYPE_1__ const**,TYPE_1__ const**) ; 

__attribute__((used)) static inline int port_group_compare_load_up(const ftree_port_group_t * p1,
                                             const ftree_port_group_t * p2)
{
        int temp = p1->counter_up - p2->counter_up;
        if (temp > 0)
                return 1;
        if (temp < 0)
                return -1;

        /* If they are both equal, choose the lowest index */
        return compare_port_groups_by_remote_switch_index (&p1,&p2);
}