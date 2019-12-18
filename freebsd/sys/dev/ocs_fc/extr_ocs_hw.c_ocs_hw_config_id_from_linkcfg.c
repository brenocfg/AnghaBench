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
typedef  scalar_t__ ocs_hw_linkcfg_e ;
struct TYPE_3__ {scalar_t__ linkcfg; size_t config_id; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* skyhawk_linkcfg_map ; 

__attribute__((used)) static uint32_t
ocs_hw_config_id_from_linkcfg(ocs_hw_linkcfg_e linkcfg)
{
	uint32_t i;
	for (i = 0; i < ARRAY_SIZE(skyhawk_linkcfg_map); i++) {
		if (skyhawk_linkcfg_map[i].linkcfg == linkcfg) {
			return skyhawk_linkcfg_map[i].config_id;
		}
	}
	return 0;
}