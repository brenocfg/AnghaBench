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
typedef  int u_int32_t ;

/* Variables and functions */
#define  AC_ADVINFO_CHANGED 141 
#define  AC_BUS_RESET 140 
#define  AC_CONTRACT 139 
#define  AC_FOUND_DEVICE 138 
#define  AC_GETDEV_CHANGED 137 
#define  AC_INQ_CHANGED 136 
#define  AC_LOST_DEVICE 135 
#define  AC_PATH_DEREGISTERED 134 
#define  AC_PATH_REGISTERED 133 
#define  AC_SCSI_AEN 132 
#define  AC_SENT_BDR 131 
#define  AC_TRANSFER_NEG 130 
#define  AC_UNIT_ATTENTION 129 
#define  AC_UNSOL_RESEL 128 

__attribute__((used)) static const char *
xpt_async_string(u_int32_t async_code)
{

	switch (async_code) {
	case AC_BUS_RESET: return ("AC_BUS_RESET");
	case AC_UNSOL_RESEL: return ("AC_UNSOL_RESEL");
	case AC_SCSI_AEN: return ("AC_SCSI_AEN");
	case AC_SENT_BDR: return ("AC_SENT_BDR");
	case AC_PATH_REGISTERED: return ("AC_PATH_REGISTERED");
	case AC_PATH_DEREGISTERED: return ("AC_PATH_DEREGISTERED");
	case AC_FOUND_DEVICE: return ("AC_FOUND_DEVICE");
	case AC_LOST_DEVICE: return ("AC_LOST_DEVICE");
	case AC_TRANSFER_NEG: return ("AC_TRANSFER_NEG");
	case AC_INQ_CHANGED: return ("AC_INQ_CHANGED");
	case AC_GETDEV_CHANGED: return ("AC_GETDEV_CHANGED");
	case AC_CONTRACT: return ("AC_CONTRACT");
	case AC_ADVINFO_CHANGED: return ("AC_ADVINFO_CHANGED");
	case AC_UNIT_ATTENTION: return ("AC_UNIT_ATTENTION");
	}
	return ("AC_UNKNOWN");
}