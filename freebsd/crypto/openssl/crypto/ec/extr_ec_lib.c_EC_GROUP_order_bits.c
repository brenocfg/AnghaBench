#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* meth; } ;
struct TYPE_5__ {int (* group_order_bits ) (TYPE_2__ const*) ;} ;
typedef  TYPE_2__ EC_GROUP ;

/* Variables and functions */
 int stub1 (TYPE_2__ const*) ; 

int EC_GROUP_order_bits(const EC_GROUP *group)
{
    return group->meth->group_order_bits(group);
}