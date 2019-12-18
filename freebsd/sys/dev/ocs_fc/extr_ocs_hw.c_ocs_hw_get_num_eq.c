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
struct TYPE_3__ {int /*<<< orphan*/  eq_count; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

int32_t
ocs_hw_get_num_eq(ocs_hw_t *hw)
{
	return hw->eq_count;
}