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
typedef  int TW_INT32 ;

/* Variables and functions */
#define  TW_CL_BAR_TYPE_IO 134 
#define  TW_CL_BAR_TYPE_MEM 133 
#define  TW_CL_BAR_TYPE_SBUF 132 
#define  TW_CL_DEVICE_ID_9K 131 
#define  TW_CL_DEVICE_ID_9K_E 130 
#define  TW_CL_DEVICE_ID_9K_SA 129 
#define  TW_CL_DEVICE_ID_9K_X 128 
 int TW_OSL_ENOTTY ; 
 int TW_OSL_ESUCCESS ; 

TW_INT32
tw_cl_get_pci_bar_info(TW_INT32 device_id, TW_INT32 bar_type,
	TW_INT32 *bar_num, TW_INT32 *bar0_offset, TW_INT32 *bar_size)
{
	TW_INT32	error = TW_OSL_ESUCCESS;

	switch(device_id) {
	case TW_CL_DEVICE_ID_9K:
		switch(bar_type) {
		case TW_CL_BAR_TYPE_IO:
			*bar_num = 0;
			*bar0_offset = 0;
			*bar_size = 4;
			break;

		case TW_CL_BAR_TYPE_MEM:
			*bar_num = 1;
			*bar0_offset = 0x4;
			*bar_size = 8;
			break;

		case TW_CL_BAR_TYPE_SBUF:
			*bar_num = 2;
			*bar0_offset = 0xC;
			*bar_size = 8;
			break;
		}
		break;

	case TW_CL_DEVICE_ID_9K_X:
	case TW_CL_DEVICE_ID_9K_E:
	case TW_CL_DEVICE_ID_9K_SA:
		switch(bar_type) {
		case TW_CL_BAR_TYPE_IO:
			*bar_num = 2;
			*bar0_offset = 0x10;
			*bar_size = 4;
			break;

		case TW_CL_BAR_TYPE_MEM:
			*bar_num = 1;
			*bar0_offset = 0x8;
			*bar_size = 8;
			break;

		case TW_CL_BAR_TYPE_SBUF:
			*bar_num = 0;
			*bar0_offset = 0;
			*bar_size = 8;
			break;
		}
		break;

	default:
		error = TW_OSL_ENOTTY;
		break;
	}

	return(error);
}