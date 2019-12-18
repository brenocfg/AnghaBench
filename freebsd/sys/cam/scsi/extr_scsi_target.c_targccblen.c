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
typedef  int xpt_opcode ;
typedef  union ccb {int dummy; } ccb ;
struct ccb_scsiio {int dummy; } ;
struct ccb_relsim {int dummy; } ;
struct ccb_pathinq {int dummy; } ;
struct ccb_immediate_notify {int dummy; } ;
struct ccb_immed_notify {int dummy; } ;
struct ccb_en_lun {int dummy; } ;
struct ccb_debug {int dummy; } ;
struct ccb_accept_tio {int dummy; } ;
struct ccb_abort {int dummy; } ;

/* Variables and functions */
#define  XPT_ABORT 137 
#define  XPT_ACCEPT_TARGET_IO 136 
#define  XPT_CONT_TARGET_IO 135 
#define  XPT_DEBUG 134 
#define  XPT_EN_LUN 133 
#define  XPT_IMMEDIATE_NOTIFY 132 
#define  XPT_IMMED_NOTIFY 131 
#define  XPT_PATH_INQ 130 
#define  XPT_REL_SIMQ 129 
#define  XPT_SCSI_IO 128 

__attribute__((used)) static size_t
targccblen(xpt_opcode func_code)
{
	int len;

	/* Codes we expect to see as a target */
	switch (func_code) {
	case XPT_CONT_TARGET_IO:
	case XPT_SCSI_IO:
		len = sizeof(struct ccb_scsiio);
		break;
	case XPT_ACCEPT_TARGET_IO:
		len = sizeof(struct ccb_accept_tio);
		break;
	case XPT_IMMED_NOTIFY:
		len = sizeof(struct ccb_immed_notify);
		break;
	case XPT_IMMEDIATE_NOTIFY:
		len = sizeof(struct ccb_immediate_notify);
		break;
	case XPT_REL_SIMQ:
		len = sizeof(struct ccb_relsim);
		break;
	case XPT_PATH_INQ:
		len = sizeof(struct ccb_pathinq);
		break;
	case XPT_DEBUG:
		len = sizeof(struct ccb_debug);
		break;
	case XPT_ABORT:
		len = sizeof(struct ccb_abort);
		break;
	case XPT_EN_LUN:
		len = sizeof(struct ccb_en_lun);
		break;
	default:
		len = sizeof(union ccb);
		break;
	}

	return (len);
}