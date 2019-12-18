#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_29__ {int* param; } ;
typedef  TYPE_1__ mbreg_t ;
struct TYPE_30__ {int isp_revision; int isp_confopts; int isp_dblev; int /*<<< orphan*/  isp_state; scalar_t__ isp_resodx; scalar_t__ isp_residx; scalar_t__ isp_reqodx; scalar_t__ isp_reqidx; scalar_t__ isp_result_dma; scalar_t__ isp_rquest_dma; } ;
typedef  TYPE_2__ ispsoftc_t ;
struct TYPE_31__ {int icb_fwoptions; scalar_t__ icb_maxfrmlen; int icb_maxalloc; int icb_execthrottle; scalar_t__ icb_hardaddr; int icb_xfwoptions; int icb_idelaytimer; int icb_zfwoptions; int icb_lunenables; int icb_ccnt; int icb_icnt; int icb_rqstqlen; int icb_rsltqlen; void** icb_respaddr; void** icb_rqstaddr; int /*<<< orphan*/  icb_portname; int /*<<< orphan*/  icb_nodename; int /*<<< orphan*/  icb_lunetimeout; int /*<<< orphan*/  icb_logintime; int /*<<< orphan*/  icb_retry_count; int /*<<< orphan*/  icb_retry_delay; int /*<<< orphan*/  icb_version; } ;
typedef  TYPE_3__ isp_icb_t ;
struct TYPE_32__ {int role; int isp_fwoptions; int isp_maxalloc; scalar_t__ isp_loopid; int isp_xfwoptions; int fctape_enabled; int isp_zfwoptions; int isp_wwnn; int isp_wwpn; int isp_scratch; scalar_t__ isp_scdma; int /*<<< orphan*/  isp_retry_count; int /*<<< orphan*/  isp_retry_delay; } ;
typedef  TYPE_4__ fcparam ;

/* Variables and functions */
 int DEFAULT_EXEC_THROTTLE (TYPE_2__*) ; 
 scalar_t__ DEFAULT_FRAMESIZE (TYPE_2__*) ; 
 void* DMA_WD0 (scalar_t__) ; 
 void* DMA_WD1 (scalar_t__) ; 
 void* DMA_WD2 (scalar_t__) ; 
 void* DMA_WD3 (scalar_t__) ; 
 TYPE_4__* FCPARAM (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FC_SCRATCH_ACQUIRE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_SCRATCH_RELEASE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ICBOPT_BOTH_WWNS ; 
 int ICBOPT_EXTENDED ; 
 int ICBOPT_FAIRNESS ; 
 int ICBOPT_FAST_POST ; 
 int ICBOPT_FULL_LOGIN ; 
 int ICBOPT_HARD_ADDRESS ; 
 int ICBOPT_INI_DISABLE ; 
 int ICBOPT_PDBCHANGE_AE ; 
 int ICBOPT_TGT_ENABLE ; 
 int ICBXOPT_FCTAPE ; 
 int ICBXOPT_FCTAPE_CCQ ; 
 int ICBXOPT_FCTAPE_CONFIRM ; 
#define  ICBXOPT_LOOP_2_PTP 138 
#define  ICBXOPT_LOOP_ONLY 137 
#define  ICBXOPT_PTP_2_LOOP 136 
#define  ICBXOPT_PTP_ONLY 135 
 int const ICBXOPT_RIO_16BIT ; 
 int ICBXOPT_TIMER_MASK ; 
 int ICBXOPT_TOPO_MASK ; 
 int ICBXOPT_ZIO ; 
#define  ICBZOPT_RATE_1GB 134 
#define  ICBZOPT_RATE_2GB 133 
#define  ICBZOPT_RATE_AUTO 132 
 int ICBZOPT_RATE_MASK ; 
 scalar_t__ ICB_DFLT_FRMLEN ; 
 int ICB_DFLT_THROTTLE ; 
 int /*<<< orphan*/  ICB_LOGIN_TOV ; 
 int /*<<< orphan*/  ICB_LUN_ENABLE_TOV ; 
 scalar_t__ ICB_MAX_FRMLEN ; 
 scalar_t__ ICB_MIN_FRMLEN ; 
 int /*<<< orphan*/  ICB_VERSION1 ; 
 int IFCOPT1_CTIO_RETRY ; 
 int IFCOPT1_DISF7SWTCH ; 
 int IFCOPT1_ENAPURE ; 
 int IFCOPT1_EQFQASYNC ; 
 int IFCOPT1_LIPASYNC ; 
 int IFCOPT1_LIPF8 ; 
 int IFCOPT3_NOPRLI ; 
 scalar_t__ ISP_CAP_FCTAPE (TYPE_2__*) ; 
 int ISP_CFG_1GB ; 
 int ISP_CFG_2GB ; 
 int ISP_CFG_FCTAPE ; 
#define  ISP_CFG_LPORT 131 
#define  ISP_CFG_LPORT_ONLY 130 
 int ISP_CFG_NOFCTAPE ; 
#define  ISP_CFG_NPORT 129 
#define  ISP_CFG_NPORT_ONLY 128 
 int ISP_CFG_OWNLOOPID ; 
 int ISP_CFG_PORT_PREF ; 
 scalar_t__ ISP_FW_NEWER_THAN (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  ISP_INITSTATE ; 
 int /*<<< orphan*/  ISP_LOGDEBUG0 ; 
 int ISP_LOGDEBUG1 ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 int /*<<< orphan*/  ISP_MEMZERO (TYPE_3__*,int) ; 
 int ISP_ROLE_INITIATOR ; 
 int ISP_ROLE_NONE ; 
 int ISP_ROLE_TARGET ; 
 int /*<<< orphan*/  ISP_RUNSTATE ; 
 scalar_t__ IS_2100 (TYPE_2__*) ; 
 scalar_t__ IS_2200 (TYPE_2__*) ; 
 scalar_t__ IS_23XX (TYPE_2__*) ; 
 scalar_t__ LOCAL_LOOP_LIM ; 
 int /*<<< orphan*/  MAKE_NODE_NAME_FROM_WWN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MBLOGALL ; 
 int MBOX_COMMAND_COMPLETE ; 
 int /*<<< orphan*/  MBOX_INIT_FIRMWARE ; 
 int /*<<< orphan*/  MBOX_SET_FIRMWARE_OPTIONS ; 
 int /*<<< orphan*/  MBSINIT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEMORYBARRIER (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int RESULT_QUEUE_LEN (TYPE_2__*) ; 
 size_t RQRSP_ADDR0015 ; 
 size_t RQRSP_ADDR1631 ; 
 size_t RQRSP_ADDR3247 ; 
 size_t RQRSP_ADDR4863 ; 
 int RQUEST_QUEUE_LEN (TYPE_2__*) ; 
 int /*<<< orphan*/  SYNC_SFORDEV ; 
 int /*<<< orphan*/  isp_mboxcmd (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  isp_print_bytes (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  isp_prt (TYPE_2__*,int,char*,...) ; 
 int /*<<< orphan*/  isp_put_icb (TYPE_2__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  sacq ; 

__attribute__((used)) static void
isp_fibre_init(ispsoftc_t *isp)
{
	fcparam *fcp;
	isp_icb_t local, *icbp = &local;
	mbreg_t mbs;
	int ownloopid;

	/*
	 * We only support one channel on non-24XX cards
	 */
	fcp = FCPARAM(isp, 0);
	if (fcp->role == ISP_ROLE_NONE)
		return;

	isp->isp_state = ISP_INITSTATE;
	ISP_MEMZERO(icbp, sizeof (*icbp));
	icbp->icb_version = ICB_VERSION1;
	icbp->icb_fwoptions = fcp->isp_fwoptions;

	/*
	 * Firmware Options are either retrieved from NVRAM or
	 * are patched elsewhere. We check them for sanity here
	 * and make changes based on board revision, but otherwise
	 * let others decide policy.
	 */

	/*
	 * If this is a 2100 < revision 5, we have to turn off FAIRNESS.
	 */
	if (IS_2100(isp) && isp->isp_revision < 5) {
		icbp->icb_fwoptions &= ~ICBOPT_FAIRNESS;
	}

	/*
	 * We have to use FULL LOGIN even though it resets the loop too much
	 * because otherwise port database entries don't get updated after
	 * a LIP- this is a known f/w bug for 2100 f/w less than 1.17.0.
	 */
	if (!ISP_FW_NEWER_THAN(isp, 1, 17, 0)) {
		icbp->icb_fwoptions |= ICBOPT_FULL_LOGIN;
	}

	/*
	 * Insist on Port Database Update Async notifications
	 */
	icbp->icb_fwoptions |= ICBOPT_PDBCHANGE_AE;

	/*
	 * Make sure that target role reflects into fwoptions.
	 */
	if (fcp->role & ISP_ROLE_TARGET) {
		icbp->icb_fwoptions |= ICBOPT_TGT_ENABLE;
	} else {
		icbp->icb_fwoptions &= ~ICBOPT_TGT_ENABLE;
	}

	/*
	 * For some reason my 2200 does not generate ATIOs in target mode
	 * if initiator is disabled.  Extra logins are better then target
	 * not working at all.
	 */
	if ((fcp->role & ISP_ROLE_INITIATOR) || IS_2100(isp) || IS_2200(isp)) {
		icbp->icb_fwoptions &= ~ICBOPT_INI_DISABLE;
	} else {
		icbp->icb_fwoptions |= ICBOPT_INI_DISABLE;
	}

	icbp->icb_maxfrmlen = DEFAULT_FRAMESIZE(isp);
	if (icbp->icb_maxfrmlen < ICB_MIN_FRMLEN || icbp->icb_maxfrmlen > ICB_MAX_FRMLEN) {
		isp_prt(isp, ISP_LOGERR, "bad frame length (%d) from NVRAM- using %d", DEFAULT_FRAMESIZE(isp), ICB_DFLT_FRMLEN);
		icbp->icb_maxfrmlen = ICB_DFLT_FRMLEN;
	}
	icbp->icb_maxalloc = fcp->isp_maxalloc;
	if (icbp->icb_maxalloc < 1) {
		isp_prt(isp, ISP_LOGERR, "bad maximum allocation (%d)- using 16", fcp->isp_maxalloc);
		icbp->icb_maxalloc = 16;
	}
	icbp->icb_execthrottle = DEFAULT_EXEC_THROTTLE(isp);
	if (icbp->icb_execthrottle < 1) {
		isp_prt(isp, ISP_LOGERR, "bad execution throttle of %d- using %d", DEFAULT_EXEC_THROTTLE(isp), ICB_DFLT_THROTTLE);
		icbp->icb_execthrottle = ICB_DFLT_THROTTLE;
	}
	icbp->icb_retry_delay = fcp->isp_retry_delay;
	icbp->icb_retry_count = fcp->isp_retry_count;
	icbp->icb_hardaddr = fcp->isp_loopid;
	ownloopid = (isp->isp_confopts & ISP_CFG_OWNLOOPID) != 0;
	if (icbp->icb_hardaddr >= LOCAL_LOOP_LIM) {
		icbp->icb_hardaddr = 0;
		ownloopid = 0;
	}

	/*
	 * Our life seems so much better with 2200s and later with
	 * the latest f/w if we set Hard Address.
	 */
	if (ownloopid || ISP_FW_NEWER_THAN(isp, 2, 2, 5)) {
		icbp->icb_fwoptions |= ICBOPT_HARD_ADDRESS;
	}

	/*
	 * Right now we just set extended options to prefer point-to-point
	 * over loop based upon some soft config options.
	 *
	 * NB: for the 2300, ICBOPT_EXTENDED is required.
	 */
	if (IS_2100(isp)) {
		/*
		 * We can't have Fast Posting any more- we now
		 * have 32 bit handles.
		 */
		icbp->icb_fwoptions &= ~ICBOPT_FAST_POST;
	} else if (IS_2200(isp) || IS_23XX(isp)) {
		icbp->icb_fwoptions |= ICBOPT_EXTENDED;

		icbp->icb_xfwoptions = fcp->isp_xfwoptions;

		if (ISP_CAP_FCTAPE(isp)) {
			if (isp->isp_confopts & ISP_CFG_NOFCTAPE)
				icbp->icb_xfwoptions &= ~ICBXOPT_FCTAPE;

			if (isp->isp_confopts & ISP_CFG_FCTAPE)
				icbp->icb_xfwoptions |= ICBXOPT_FCTAPE;

			if (icbp->icb_xfwoptions & ICBXOPT_FCTAPE) {
				icbp->icb_fwoptions &= ~ICBOPT_FULL_LOGIN;	/* per documents */
				icbp->icb_xfwoptions |= ICBXOPT_FCTAPE_CCQ|ICBXOPT_FCTAPE_CONFIRM;
				FCPARAM(isp, 0)->fctape_enabled = 1;
			} else {
				FCPARAM(isp, 0)->fctape_enabled = 0;
			}
		} else {
			icbp->icb_xfwoptions &= ~ICBXOPT_FCTAPE;
			FCPARAM(isp, 0)->fctape_enabled = 0;
		}

		/*
		 * Prefer or force Point-To-Point instead Loop?
		 */
		switch (isp->isp_confopts & ISP_CFG_PORT_PREF) {
		case ISP_CFG_LPORT_ONLY:
			icbp->icb_xfwoptions &= ~ICBXOPT_TOPO_MASK;
			icbp->icb_xfwoptions |= ICBXOPT_LOOP_ONLY;
			break;
		case ISP_CFG_NPORT_ONLY:
			icbp->icb_xfwoptions &= ~ICBXOPT_TOPO_MASK;
			icbp->icb_xfwoptions |= ICBXOPT_PTP_ONLY;
			break;
		case ISP_CFG_LPORT:
			icbp->icb_xfwoptions &= ~ICBXOPT_TOPO_MASK;
			icbp->icb_xfwoptions |= ICBXOPT_LOOP_2_PTP;
			break;
		case ISP_CFG_NPORT:
			icbp->icb_xfwoptions &= ~ICBXOPT_TOPO_MASK;
			icbp->icb_xfwoptions |= ICBXOPT_PTP_2_LOOP;
			break;
		default:
			/* Let NVRAM settings define it if they are sane */
			switch (icbp->icb_xfwoptions & ICBXOPT_TOPO_MASK) {
			case ICBXOPT_PTP_2_LOOP:
			case ICBXOPT_PTP_ONLY:
			case ICBXOPT_LOOP_ONLY:
			case ICBXOPT_LOOP_2_PTP:
				break;
			default:
				icbp->icb_xfwoptions &= ~ICBXOPT_TOPO_MASK;
				icbp->icb_xfwoptions |= ICBXOPT_LOOP_2_PTP;
			}
			break;
		}
		if (IS_2200(isp)) {
			/*
			 * We can't have Fast Posting any more- we now
			 * have 32 bit handles.
			 *
			 * RIO seemed to have to much breakage.
			 *
			 * Just opt for safety.
			 */
			icbp->icb_xfwoptions &= ~ICBXOPT_RIO_16BIT;
			icbp->icb_fwoptions &= ~ICBOPT_FAST_POST;
		} else {
			/*
			 * QLogic recommends that FAST Posting be turned
			 * off for 23XX cards and instead allow the HBA
			 * to write response queue entries and interrupt
			 * after a delay (ZIO).
			 */
			icbp->icb_fwoptions &= ~ICBOPT_FAST_POST;
			if ((fcp->isp_xfwoptions & ICBXOPT_TIMER_MASK) == ICBXOPT_ZIO) {
				icbp->icb_xfwoptions |= ICBXOPT_ZIO;
				icbp->icb_idelaytimer = 10;
			}
			icbp->icb_zfwoptions = fcp->isp_zfwoptions;
			if (isp->isp_confopts & ISP_CFG_1GB) {
				icbp->icb_zfwoptions &= ~ICBZOPT_RATE_MASK;
				icbp->icb_zfwoptions |= ICBZOPT_RATE_1GB;
			} else if (isp->isp_confopts & ISP_CFG_2GB) {
				icbp->icb_zfwoptions &= ~ICBZOPT_RATE_MASK;
				icbp->icb_zfwoptions |= ICBZOPT_RATE_2GB;
			} else {
				switch (icbp->icb_zfwoptions & ICBZOPT_RATE_MASK) {
				case ICBZOPT_RATE_1GB:
				case ICBZOPT_RATE_2GB:
				case ICBZOPT_RATE_AUTO:
					break;
				default:
					icbp->icb_zfwoptions &= ~ICBZOPT_RATE_MASK;
					icbp->icb_zfwoptions |= ICBZOPT_RATE_AUTO;
					break;
				}
			}
		}
	}


	/*
	 * For 22XX > 2.1.26 && 23XX, set some options.
	 */
	if (ISP_FW_NEWER_THAN(isp, 2, 26, 0)) {
		MBSINIT(&mbs, MBOX_SET_FIRMWARE_OPTIONS, MBLOGALL, 0);
		mbs.param[1] = IFCOPT1_DISF7SWTCH|IFCOPT1_LIPASYNC|IFCOPT1_LIPF8;
		mbs.param[2] = 0;
		mbs.param[3] = 0;
		if (ISP_FW_NEWER_THAN(isp, 3, 16, 0)) {
			mbs.param[1] |= IFCOPT1_EQFQASYNC|IFCOPT1_CTIO_RETRY;
			if (fcp->role & ISP_ROLE_TARGET) {
				if (ISP_FW_NEWER_THAN(isp, 3, 25, 0)) {
					mbs.param[1] |= IFCOPT1_ENAPURE;
				}
				mbs.param[3] = IFCOPT3_NOPRLI;
			}
		}
		isp_mboxcmd(isp, &mbs);
		if (mbs.param[0] != MBOX_COMMAND_COMPLETE) {
			return;
		}
	}
	icbp->icb_logintime = ICB_LOGIN_TOV;

#ifdef	ISP_TARGET_MODE
	if (icbp->icb_fwoptions & ICBOPT_TGT_ENABLE) {
		icbp->icb_lunenables = 0xffff;
		icbp->icb_ccnt = 0xff;
		icbp->icb_icnt = 0xff;
		icbp->icb_lunetimeout = ICB_LUN_ENABLE_TOV;
	}
#endif
	if (fcp->isp_wwnn && fcp->isp_wwpn) {
		icbp->icb_fwoptions |= ICBOPT_BOTH_WWNS;
		MAKE_NODE_NAME_FROM_WWN(icbp->icb_nodename, fcp->isp_wwnn);
		MAKE_NODE_NAME_FROM_WWN(icbp->icb_portname, fcp->isp_wwpn);
		isp_prt(isp, ISP_LOGDEBUG1,
		    "Setting ICB Node 0x%08x%08x Port 0x%08x%08x",
		    ((uint32_t) (fcp->isp_wwnn >> 32)),
		    ((uint32_t) (fcp->isp_wwnn)),
		    ((uint32_t) (fcp->isp_wwpn >> 32)),
		    ((uint32_t) (fcp->isp_wwpn)));
	} else if (fcp->isp_wwpn) {
		icbp->icb_fwoptions &= ~ICBOPT_BOTH_WWNS;
		MAKE_NODE_NAME_FROM_WWN(icbp->icb_portname, fcp->isp_wwpn);
		isp_prt(isp, ISP_LOGDEBUG1,
		    "Setting ICB Port 0x%08x%08x",
		    ((uint32_t) (fcp->isp_wwpn >> 32)),
		    ((uint32_t) (fcp->isp_wwpn)));
	} else {
		isp_prt(isp, ISP_LOGERR, "No valid WWNs to use");
		return;
	}
	icbp->icb_rqstqlen = RQUEST_QUEUE_LEN(isp);
	if (icbp->icb_rqstqlen < 1) {
		isp_prt(isp, ISP_LOGERR, "bad request queue length");
	}
	icbp->icb_rsltqlen = RESULT_QUEUE_LEN(isp);
	if (icbp->icb_rsltqlen < 1) {
		isp_prt(isp, ISP_LOGERR, "bad result queue length");
	}
	icbp->icb_rqstaddr[RQRSP_ADDR0015] = DMA_WD0(isp->isp_rquest_dma);
	icbp->icb_rqstaddr[RQRSP_ADDR1631] = DMA_WD1(isp->isp_rquest_dma);
	icbp->icb_rqstaddr[RQRSP_ADDR3247] = DMA_WD2(isp->isp_rquest_dma);
	icbp->icb_rqstaddr[RQRSP_ADDR4863] = DMA_WD3(isp->isp_rquest_dma);
	icbp->icb_respaddr[RQRSP_ADDR0015] = DMA_WD0(isp->isp_result_dma);
	icbp->icb_respaddr[RQRSP_ADDR1631] = DMA_WD1(isp->isp_result_dma);
	icbp->icb_respaddr[RQRSP_ADDR3247] = DMA_WD2(isp->isp_result_dma);
	icbp->icb_respaddr[RQRSP_ADDR4863] = DMA_WD3(isp->isp_result_dma);

	if (FC_SCRATCH_ACQUIRE(isp, 0)) {
		isp_prt(isp, ISP_LOGERR, sacq);
		return;
	}
	isp_prt(isp, ISP_LOGDEBUG0, "isp_fibre_init: fwopt 0x%x xfwopt 0x%x zfwopt 0x%x",
	    icbp->icb_fwoptions, icbp->icb_xfwoptions, icbp->icb_zfwoptions);

	isp_put_icb(isp, icbp, (isp_icb_t *)fcp->isp_scratch);
	if (isp->isp_dblev & ISP_LOGDEBUG1) {
		isp_print_bytes(isp, "isp_fibre_init",
		    sizeof(*icbp), fcp->isp_scratch);
	}

	/*
	 * Init the firmware
	 */
	MBSINIT(&mbs, MBOX_INIT_FIRMWARE, MBLOGALL, 30000000);
	mbs.param[1] = 0;
	mbs.param[2] = DMA_WD1(fcp->isp_scdma);
	mbs.param[3] = DMA_WD0(fcp->isp_scdma);
	mbs.param[6] = DMA_WD3(fcp->isp_scdma);
	mbs.param[7] = DMA_WD2(fcp->isp_scdma);
	isp_prt(isp, ISP_LOGDEBUG0, "INIT F/W from %p (%08x%08x)",
	    fcp->isp_scratch, (uint32_t) ((uint64_t)fcp->isp_scdma >> 32),
	    (uint32_t) fcp->isp_scdma);
	MEMORYBARRIER(isp, SYNC_SFORDEV, 0, sizeof (*icbp), 0);
	isp_mboxcmd(isp, &mbs);
	FC_SCRATCH_RELEASE(isp, 0);
	if (mbs.param[0] != MBOX_COMMAND_COMPLETE)
		return;
	isp->isp_reqidx = 0;
	isp->isp_reqodx = 0;
	isp->isp_residx = 0;
	isp->isp_resodx = 0;

	/*
	 * Whatever happens, we're now committed to being here.
	 */
	isp->isp_state = ISP_RUNSTATE;
}