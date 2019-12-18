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
struct TYPE_3__ {int /*<<< orphan*/  linkcfg; int /*<<< orphan*/  mgmt_str; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  OCS_HW_LINKCFG_NA ; 
 TYPE_1__* mgmt_linkcfg_map ; 
 int /*<<< orphan*/  ocs_strlen (char const*) ; 
 scalar_t__ ocs_strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ocs_hw_linkcfg_e
ocs_hw_linkcfg_from_mgmt(const char *mgmt_str)
{
	uint32_t i;
	for (i = 0; i < ARRAY_SIZE(mgmt_linkcfg_map); i++) {
		if (ocs_strncmp(mgmt_linkcfg_map[i].mgmt_str,
				mgmt_str, ocs_strlen(mgmt_str)) == 0) {
			return mgmt_linkcfg_map[i].linkcfg;
		}
	}
	return OCS_HW_LINKCFG_NA;
}