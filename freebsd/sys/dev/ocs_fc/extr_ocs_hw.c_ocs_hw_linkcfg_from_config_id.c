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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ocs_hw_linkcfg_e ;
struct TYPE_3__ {size_t const config_id; int /*<<< orphan*/  linkcfg; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  OCS_HW_LINKCFG_NA ; 
 TYPE_1__* skyhawk_linkcfg_map ; 

__attribute__((used)) static ocs_hw_linkcfg_e
ocs_hw_linkcfg_from_config_id(const uint32_t config_id)
{
	uint32_t i;
	for (i = 0; i < ARRAY_SIZE(skyhawk_linkcfg_map); i++) {
		if (skyhawk_linkcfg_map[i].config_id == config_id) {
			return skyhawk_linkcfg_map[i].linkcfg;
		}
	}
	return OCS_HW_LINKCFG_NA;
}