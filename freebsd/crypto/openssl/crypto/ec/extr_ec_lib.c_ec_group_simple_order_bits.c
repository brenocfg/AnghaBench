#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * order; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int BN_num_bits (int /*<<< orphan*/ *) ; 

int ec_group_simple_order_bits(const EC_GROUP *group)
{
    if (group->order == NULL)
        return 0;
    return BN_num_bits(group->order);
}