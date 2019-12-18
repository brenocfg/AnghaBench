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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
#define  OCS_HW_ELS_REQ 132 
#define  OCS_HW_FC_CT 131 
#define  OCS_HW_IO_INITIATOR_NODATA 130 
#define  OCS_HW_IO_INITIATOR_READ 129 
#define  OCS_HW_IO_INITIATOR_WRITE 128 

__attribute__((used)) static uint8_t ocs_hw_iotype_is_originator(uint16_t io_type)
{
	switch (io_type) {
	case OCS_HW_IO_INITIATOR_READ:
	case OCS_HW_IO_INITIATOR_WRITE:
	case OCS_HW_IO_INITIATOR_NODATA:
	case OCS_HW_FC_CT:
	case OCS_HW_ELS_REQ:
		return 1;
	default:
		return 0;
	}
}