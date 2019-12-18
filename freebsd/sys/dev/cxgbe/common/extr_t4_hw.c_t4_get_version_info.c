#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vpd_vers; int /*<<< orphan*/  scfg_vers; int /*<<< orphan*/  er_vers; int /*<<< orphan*/  tp_vers; int /*<<< orphan*/  bs_vers; int /*<<< orphan*/  fw_vers; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_get_bs_version (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_get_exprom_version (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_get_fw_version (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_get_scfg_version (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_get_tp_version (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_get_vpd_version (struct adapter*,int /*<<< orphan*/ *) ; 

int t4_get_version_info(struct adapter *adapter)
{
	int ret = 0;

	#define FIRST_RET(__getvinfo) \
	do { \
		int __ret = __getvinfo; \
		if (__ret && !ret) \
			ret = __ret; \
	} while (0)

	FIRST_RET(t4_get_fw_version(adapter, &adapter->params.fw_vers));
	FIRST_RET(t4_get_bs_version(adapter, &adapter->params.bs_vers));
	FIRST_RET(t4_get_tp_version(adapter, &adapter->params.tp_vers));
	FIRST_RET(t4_get_exprom_version(adapter, &adapter->params.er_vers));
	FIRST_RET(t4_get_scfg_version(adapter, &adapter->params.scfg_vers));
	FIRST_RET(t4_get_vpd_version(adapter, &adapter->params.vpd_vers));

	#undef FIRST_RET

	return ret;
}