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
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_NIC2E 129 
#define  CVMX_BOARD_TYPE_NIC_XLE_4G 128 
 TYPE_1__* cvmx_sysinfo_get () ; 

int __cvmx_helper_board_usb_get_num_ports(int supported_ports)
{
    switch (cvmx_sysinfo_get()->board_type)
    {
        case CVMX_BOARD_TYPE_NIC_XLE_4G:
        case CVMX_BOARD_TYPE_NIC2E:
            return 0;
    }

    return supported_ports;
}