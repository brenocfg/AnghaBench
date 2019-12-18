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
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_ArcJtagEnable (DSL_DEV_Device_t *dev, int enable)
{
	/*
	int meierr=0;
	u32 reg_data;
	switch (enable) {
	case 1:
                //reserve gpio 9, 10, 11, 14, 19 for ARC JTAG
		ifxmips_port_reserve_pin (0, 9);
		ifxmips_port_reserve_pin (0, 10);
		ifxmips_port_reserve_pin (0, 11);
		ifxmips_port_reserve_pin (0, 14);
		ifxmips_port_reserve_pin (1, 3);

		ifxmips_port_set_dir_in(0, 11);
		ifxmips_port_clear_altsel0(0, 11);
		ifxmips_port_clear_altsel1(0, 11);
		ifxmips_port_set_open_drain(0, 11);
        //enable ARC JTAG
        IFX_MEI_LongWordRead ((u32) LTQ_RCU_RST, &reg_data);
        IFX_MEI_LongWordWrite ((u32) LTQ_RCU_RST, reg_data | LTQ_RCU_RST_REQ_ARC_JTAG);
		break;
	case 0:
	default:
		break;
	}
jtag_end:
	if (meierr)
		return DSL_DEV_MEI_ERR_FAILURE;
*/

	return DSL_DEV_MEI_ERR_SUCCESS;
}