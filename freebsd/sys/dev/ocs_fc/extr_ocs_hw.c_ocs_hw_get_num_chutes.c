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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;

/* Variables and functions */
 scalar_t__ sli_get_is_dual_ulp_capable (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_get_is_ulp_enabled (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
ocs_hw_get_num_chutes(ocs_hw_t *hw)
{
	uint32_t num_chutes = 1;

	if (sli_get_is_dual_ulp_capable(&hw->sli) &&
	    sli_get_is_ulp_enabled(&hw->sli, 0) &&
	    sli_get_is_ulp_enabled(&hw->sli, 1)) {
		num_chutes = 2;
	}
	return num_chutes;
}