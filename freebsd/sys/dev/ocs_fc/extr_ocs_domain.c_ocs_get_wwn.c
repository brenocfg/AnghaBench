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
typedef  int /*<<< orphan*/  value ;
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_property_e ;

/* Variables and functions */
 int* ocs_hw_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint64_t
ocs_get_wwn(ocs_hw_t *hw, ocs_hw_property_e prop)
{
	uint8_t *p = ocs_hw_get_ptr(hw, prop);
	uint64_t value = 0;

	if (p) {
		uint32_t i;
		for (i = 0; i < sizeof(value); i++) {
			value = (value << 8) | p[i];
		}
	}
	return value;
}