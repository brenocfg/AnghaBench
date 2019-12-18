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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {scalar_t__ device_id; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 scalar_t__ QLOGIC_PCI_DEVICE_ID_1634 ; 
 scalar_t__ QLOGIC_PCI_DEVICE_ID_1644 ; 
 scalar_t__ QLOGIC_PCI_DEVICE_ID_1654 ; 
 scalar_t__ QLOGIC_PCI_DEVICE_ID_1656 ; 
 scalar_t__ QLOGIC_PCI_DEVICE_ID_8070 ; 
 scalar_t__ QLOGIC_PCI_DEVICE_ID_8090 ; 

__attribute__((used)) static int
qlnx_valid_device(qlnx_host_t *ha)
{
        uint16_t device_id;

        device_id = ha->device_id;

#ifndef QLNX_VF
        if ((device_id == QLOGIC_PCI_DEVICE_ID_1634) ||
                (device_id == QLOGIC_PCI_DEVICE_ID_1644) ||
                (device_id == QLOGIC_PCI_DEVICE_ID_1656) ||
                (device_id == QLOGIC_PCI_DEVICE_ID_1654) ||
                (device_id == QLOGIC_PCI_DEVICE_ID_8070))
                return 0;
#else
        if (device_id == QLOGIC_PCI_DEVICE_ID_8090)
		return 0;

#endif /* #ifndef QLNX_VF */
        return -1;
}