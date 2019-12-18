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
struct TYPE_3__ {int isp_dblev; int /*<<< orphan*/  isp_confopts; } ;
typedef  TYPE_1__ ispsoftc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_CFG_NONVRAM ; 
 int /*<<< orphan*/  ISP_CFG_NORELOAD ; 
 int ISP_LOGCONFIG ; 
 int ISP_LOGERR ; 
 int ISP_LOGINFO ; 
 int ISP_LOGWARN ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int isp_nvports ; 
 int isp_quickboot_time ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void
isp_get_generic_options(device_t dev, ispsoftc_t *isp)
{
	int tval;

	tval = 0;
	if (resource_int_value(device_get_name(dev), device_get_unit(dev), "fwload_disable", &tval) == 0 && tval != 0) {
		isp->isp_confopts |= ISP_CFG_NORELOAD;
	}
	tval = 0;
	if (resource_int_value(device_get_name(dev), device_get_unit(dev), "ignore_nvram", &tval) == 0 && tval != 0) {
		isp->isp_confopts |= ISP_CFG_NONVRAM;
	}
	tval = 0;
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev), "debug", &tval);
	if (tval) {
		isp->isp_dblev = tval;
	} else {
		isp->isp_dblev = ISP_LOGWARN|ISP_LOGERR;
	}
	if (bootverbose) {
		isp->isp_dblev |= ISP_LOGCONFIG|ISP_LOGINFO;
	}
	tval = -1;
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev), "vports", &tval);
	if (tval > 0 && tval <= 254) {
		isp_nvports = tval;
	}
	tval = 7;
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev), "quickboot_time", &tval);
	isp_quickboot_time = tval;
}