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
struct ccb_trans_settings {int dummy; } ;
struct ccb_scsiio {int dummy; } ;
struct ccb_pathinq {int dummy; } ;
struct ccb_getdev {int dummy; } ;
struct ac_contract {int dummy; } ;

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

__attribute__((used)) static int
xpt_async_size(u_int32_t async_code)
{

	switch (async_code) {
	case AC_BUS_RESET: return (0);
	case AC_UNSOL_RESEL: return (0);
	case AC_SCSI_AEN: return (0);
	case AC_SENT_BDR: return (0);
	case AC_PATH_REGISTERED: return (sizeof(struct ccb_pathinq));
	case AC_PATH_DEREGISTERED: return (0);
	case AC_FOUND_DEVICE: return (sizeof(struct ccb_getdev));
	case AC_LOST_DEVICE: return (0);
	case AC_TRANSFER_NEG: return (sizeof(struct ccb_trans_settings));
	case AC_INQ_CHANGED: return (0);
	case AC_GETDEV_CHANGED: return (0);
	case AC_CONTRACT: return (sizeof(struct ac_contract));
	case AC_ADVINFO_CHANGED: return (-1);
	case AC_UNIT_ATTENTION: return (sizeof(struct ccb_scsiio));
	}
	return (0);
}