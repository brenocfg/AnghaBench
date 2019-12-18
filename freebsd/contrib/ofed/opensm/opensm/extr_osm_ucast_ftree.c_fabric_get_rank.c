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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ leaf_switch_rank; } ;
typedef  TYPE_1__ ftree_fabric_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t fabric_get_rank(ftree_fabric_t * p_ftree)
{
	return p_ftree->leaf_switch_rank + 1;
}