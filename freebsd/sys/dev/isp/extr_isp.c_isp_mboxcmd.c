#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mname ;
struct TYPE_14__ {unsigned int* param; unsigned int ibits; unsigned int obits; unsigned int ibitm; unsigned int obitm; int logval; } ;
typedef  TYPE_1__ mbreg_t ;
struct TYPE_15__ {int* isp_mboxtmp; unsigned int isp_lastmbxcmd; unsigned int isp_obits; int isp_mboxbsy; } ;
typedef  TYPE_2__ ispsoftc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIU2400_HCCR ; 
 int /*<<< orphan*/  HCCR ; 
 int HCCR_2400_CMD_SET_HOST_INT ; 
 int HCCR_CMD_SET_HOST_INT ; 
 unsigned int ISP_FC_IBITS (unsigned int) ; 
 unsigned int ISP_FC_OBITS (unsigned int) ; 
 int /*<<< orphan*/  ISP_LOGALL ; 
 int /*<<< orphan*/  ISP_LOGDEBUG3 ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 unsigned int ISP_NMBOX (TYPE_2__*) ; 
 unsigned int ISP_SCSI_IBITS (unsigned int) ; 
 unsigned int ISP_SCSI_OBITS (unsigned int) ; 
 int /*<<< orphan*/  ISP_SNPRINTF (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  ISP_WRITE (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_24XX (TYPE_2__*) ; 
 scalar_t__ IS_FC (TYPE_2__*) ; 
 unsigned int MAX_FC_OPCODE ; 
 unsigned int MAX_SCSI_OPCODE ; 
 int MBLOGMASK (int) ; 
 scalar_t__ MBOX_ACQUIRE (TYPE_2__*) ; 
#define  MBOX_ALL_IDS_USED 142 
#define  MBOX_CHECKSUM_ERROR 141 
 int MBOX_COMMAND_COMPLETE ; 
#define  MBOX_COMMAND_ERROR 140 
#define  MBOX_COMMAND_PARAM_ERROR 139 
#define  MBOX_HOST_INTERFACE_ERROR 138 
#define  MBOX_INVALID_COMMAND 137 
#define  MBOX_INVALID_PRODUCT_KEY 136 
#define  MBOX_LINK_DOWN_ERROR 135 
#define  MBOX_LOOPBACK_ERROR 134 
#define  MBOX_LOOP_ID_USED 133 
#define  MBOX_NOT_LOGGED_IN 132 
 int /*<<< orphan*/  MBOX_OFF (unsigned int) ; 
#define  MBOX_PORT_ID_USED 131 
#define  MBOX_REGS_BUSY 130 
 int /*<<< orphan*/  MBOX_RELEASE (TYPE_2__*) ; 
#define  MBOX_TEST_FAILED 129 
#define  MBOX_TIMEOUT 128 
 int /*<<< orphan*/  MBOX_WAIT_COMPLETE (TYPE_2__*,TYPE_1__*) ; 
 char** fc_mbcmd_names ; 
 int /*<<< orphan*/  isp_prt (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 char** scsi_mbcmd_names ; 

__attribute__((used)) static void
isp_mboxcmd(ispsoftc_t *isp, mbreg_t *mbp)
{
	const char *cname, *xname, *sname;
	char tname[16], mname[16];
	unsigned int ibits, obits, box, opcode;

	opcode = mbp->param[0];
	if (IS_FC(isp)) {
		if (opcode > MAX_FC_OPCODE) {
			mbp->param[0] = MBOX_INVALID_COMMAND;
			isp_prt(isp, ISP_LOGERR, "Unknown Command 0x%x", opcode);
			return;
		}
		cname = fc_mbcmd_names[opcode];
		ibits = ISP_FC_IBITS(opcode);
		obits = ISP_FC_OBITS(opcode);
	} else {
		if (opcode > MAX_SCSI_OPCODE) {
			mbp->param[0] = MBOX_INVALID_COMMAND;
			isp_prt(isp, ISP_LOGERR, "Unknown Command 0x%x", opcode);
			return;
		}
		cname = scsi_mbcmd_names[opcode];
		ibits = ISP_SCSI_IBITS(opcode);
		obits = ISP_SCSI_OBITS(opcode);
	}
	if (cname == NULL) {
		cname = tname;
		ISP_SNPRINTF(tname, sizeof tname, "opcode %x", opcode);
	}
	isp_prt(isp, ISP_LOGDEBUG3, "Mailbox Command '%s'", cname);

	/*
	 * Pick up any additional bits that the caller might have set.
	 */
	ibits |= mbp->ibits;
	obits |= mbp->obits;

	/*
	 * Mask any bits that the caller wants us to mask
	 */
	ibits &= mbp->ibitm;
	obits &= mbp->obitm;


	if (ibits == 0 && obits == 0) {
		mbp->param[0] = MBOX_COMMAND_PARAM_ERROR;
		isp_prt(isp, ISP_LOGERR, "no parameters for 0x%x", opcode);
		return;
	}

	/*
	 * Get exclusive usage of mailbox registers.
	 */
	if (MBOX_ACQUIRE(isp)) {
		mbp->param[0] = MBOX_REGS_BUSY;
		goto out;
	}

	for (box = 0; box < ISP_NMBOX(isp); box++) {
		if (ibits & (1 << box)) {
			isp_prt(isp, ISP_LOGDEBUG3, "IN mbox %d = 0x%04x", box,
			    mbp->param[box]);
			ISP_WRITE(isp, MBOX_OFF(box), mbp->param[box]);
		}
		isp->isp_mboxtmp[box] = mbp->param[box] = 0;
	}

	isp->isp_lastmbxcmd = opcode;

	/*
	 * We assume that we can't overwrite a previous command.
	 */
	isp->isp_obits = obits;
	isp->isp_mboxbsy = 1;

	/*
	 * Set Host Interrupt condition so that RISC will pick up mailbox regs.
	 */
	if (IS_24XX(isp)) {
		ISP_WRITE(isp, BIU2400_HCCR, HCCR_2400_CMD_SET_HOST_INT);
	} else {
		ISP_WRITE(isp, HCCR, HCCR_CMD_SET_HOST_INT);
	}

	/*
	 * While we haven't finished the command, spin our wheels here.
	 */
	MBOX_WAIT_COMPLETE(isp, mbp);

	/*
	 * Did the command time out?
	 */
	if (mbp->param[0] == MBOX_TIMEOUT) {
		isp->isp_mboxbsy = 0;
		MBOX_RELEASE(isp);
		goto out;
	}

	/*
	 * Copy back output registers.
	 */
	for (box = 0; box < ISP_NMBOX(isp); box++) {
		if (obits & (1 << box)) {
			mbp->param[box] = isp->isp_mboxtmp[box];
			isp_prt(isp, ISP_LOGDEBUG3, "OUT mbox %d = 0x%04x", box,
			    mbp->param[box]);
		}
	}

	isp->isp_mboxbsy = 0;
	MBOX_RELEASE(isp);
out:
	if (mbp->logval == 0 || mbp->param[0] == MBOX_COMMAND_COMPLETE)
		return;

	if ((mbp->param[0] & 0xbfe0) == 0 &&
	    (mbp->logval & MBLOGMASK(mbp->param[0])) == 0)
		return;

	xname = NULL;
	sname = "";
	switch (mbp->param[0]) {
	case MBOX_INVALID_COMMAND:
		xname = "INVALID COMMAND";
		break;
	case MBOX_HOST_INTERFACE_ERROR:
		xname = "HOST INTERFACE ERROR";
		break;
	case MBOX_TEST_FAILED:
		xname = "TEST FAILED";
		break;
	case MBOX_COMMAND_ERROR:
		xname = "COMMAND ERROR";
		ISP_SNPRINTF(mname, sizeof(mname), " subcode 0x%x",
		    mbp->param[1]);
		sname = mname;
		break;
	case MBOX_COMMAND_PARAM_ERROR:
		xname = "COMMAND PARAMETER ERROR";
		break;
	case MBOX_PORT_ID_USED:
		xname = "PORT ID ALREADY IN USE";
		break;
	case MBOX_LOOP_ID_USED:
		xname = "LOOP ID ALREADY IN USE";
		break;
	case MBOX_ALL_IDS_USED:
		xname = "ALL LOOP IDS IN USE";
		break;
	case MBOX_NOT_LOGGED_IN:
		xname = "NOT LOGGED IN";
		break;
	case MBOX_LINK_DOWN_ERROR:
		xname = "LINK DOWN ERROR";
		break;
	case MBOX_LOOPBACK_ERROR:
		xname = "LOOPBACK ERROR";
		break;
	case MBOX_CHECKSUM_ERROR:
		xname = "CHECKSUM ERROR";
		break;
	case MBOX_INVALID_PRODUCT_KEY:
		xname = "INVALID PRODUCT KEY";
		break;
	case MBOX_REGS_BUSY:
		xname = "REGISTERS BUSY";
		break;
	case MBOX_TIMEOUT:
		xname = "TIMEOUT";
		break;
	default:
		ISP_SNPRINTF(mname, sizeof mname, "error 0x%x", mbp->param[0]);
		xname = mname;
		break;
	}
	if (xname) {
		isp_prt(isp, ISP_LOGALL, "Mailbox Command '%s' failed (%s%s)",
		    cname, xname, sname);
	}
}