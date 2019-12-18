#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_11__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_36__ {int majorRev; scalar_t__ minorRev; } ;
typedef  TYPE_8__ t_QmRevisionInfo ;
struct TYPE_35__ {int /*<<< orphan*/  redCurve; scalar_t__ enableRed; int /*<<< orphan*/  yellowCurve; scalar_t__ enableYellow; int /*<<< orphan*/  greenCurve; scalar_t__ enableGreen; } ;
struct TYPE_37__ {scalar_t__ dcPortalId; int threshold; int /*<<< orphan*/  p_LowQmPortal; scalar_t__ f_Exception; scalar_t__ notifyDcPortal; scalar_t__ tailDropEnable; TYPE_7__ wredParams; scalar_t__ wredEnable; scalar_t__ frameCount; struct TYPE_37__* h_Qm; int /*<<< orphan*/  h_App; struct TYPE_37__* h_QmPortal; } ;
typedef  TYPE_9__ t_QmPortal ;
typedef  TYPE_9__ t_QmCgParams ;
struct TYPE_28__ {TYPE_9__* h_QmPortal; scalar_t__ f_Exception; TYPE_9__* h_Qm; int /*<<< orphan*/  id; int /*<<< orphan*/  h_App; } ;
typedef  TYPE_11__ t_QmCg ;
typedef  TYPE_11__* t_Handle ;
typedef  scalar_t__ t_Error ;
struct qm_mc_result {int verb; scalar_t__ result; } ;
struct TYPE_31__ {int TA; int Tn; } ;
struct TYPE_30__ {int word; } ;
struct TYPE_29__ {int word; } ;
struct TYPE_32__ {int word; } ;
struct TYPE_33__ {int cscn_targ; TYPE_3__ cs_thres; void* cscn_en; void* cstd_en; TYPE_2__ wr_parm_r; void* wr_en_r; TYPE_1__ wr_parm_y; void* wr_en_y; TYPE_4__ wr_parm_g; void* wr_en_g; void* frame_mode; } ;
struct TYPE_34__ {int we_mask; TYPE_5__ cgr; int /*<<< orphan*/  cgid; } ;
struct qm_mc_command {TYPE_6__ initcgr; } ;

/* Variables and functions */
 int ABS (int) ; 
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 scalar_t__ CalcWredCurve (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ E_INVALID_HANDLE ; 
 scalar_t__ E_INVALID_STATE ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_NO_MEMORY ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NCSW_PLOCK (TYPE_9__*) ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_9__*) ; 
 void* QM_CGR_EN ; 
 scalar_t__ QM_CGR_TARGET_DCP (scalar_t__) ; 
 scalar_t__ QM_CGR_TARGET_SWP (int /*<<< orphan*/ ) ; 
 int QM_CGR_WE_CSCN_EN ; 
 int QM_CGR_WE_CSCN_TARG ; 
 int QM_CGR_WE_CSTD_EN ; 
 int QM_CGR_WE_CS_THRES ; 
 int QM_CGR_WE_MODE ; 
 int QM_CGR_WE_WR_EN_G ; 
 int QM_CGR_WE_WR_EN_R ; 
 int QM_CGR_WE_WR_EN_Y ; 
 int QM_CGR_WE_WR_PARM_G ; 
 int QM_CGR_WE_WR_PARM_R ; 
 int QM_CGR_WE_WR_PARM_Y ; 
 int QM_MCC_VERB_INITCGR ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 int QM_MCR_VERB_MASK ; 
 scalar_t__ QmGetCgId (TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_9__* QmGetPortalHandle (TYPE_9__*) ; 
 int /*<<< orphan*/  QmGetRevision (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  QmPortalGetSwPortalId (TYPE_9__*) ; 
 scalar_t__ QmPortalRegisterCg (TYPE_9__*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_9__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_Free (TYPE_11__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 scalar_t__ e_DPAA_DCPORTAL2 ; 
 scalar_t__ e_DPAA_DCPORTAL3 ; 
 int /*<<< orphan*/  mcr_result_str (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ ,int) ; 
 struct qm_mc_result* qm_mc_result (int /*<<< orphan*/ ) ; 
 struct qm_mc_command* qm_mc_start (int /*<<< orphan*/ ) ; 

t_Handle QM_CG_Create(t_QmCgParams *p_CgParams)
{
    t_QmCg                          *p_QmCg;
    t_QmPortal                      *p_QmPortal;
    t_Error                         err;
    uint32_t                        wredParams;
    uint32_t                        tmpA, tmpN, ta=0, tn=0;
    int                             gap, tmp;
    struct qm_mc_command            *p_Mcc;
    struct qm_mc_result             *p_Mcr;

    SANITY_CHECK_RETURN_VALUE(p_CgParams, E_INVALID_HANDLE, NULL);
    SANITY_CHECK_RETURN_VALUE(p_CgParams->h_Qm, E_INVALID_HANDLE, NULL);

    if(p_CgParams->notifyDcPortal &&
       ((p_CgParams->dcPortalId == e_DPAA_DCPORTAL2) || (p_CgParams->dcPortalId == e_DPAA_DCPORTAL3)))
    {
        REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("notifyDcPortal is invalid for this DC Portal"));
        return NULL;
    }

    if (!p_CgParams->h_QmPortal)
    {
        p_QmPortal = QmGetPortalHandle(p_CgParams->h_Qm);
        SANITY_CHECK_RETURN_VALUE(p_QmPortal, E_INVALID_STATE, NULL);
    }
    else
        p_QmPortal = p_CgParams->h_QmPortal;

    p_QmCg = (t_QmCg *)XX_Malloc(sizeof(t_QmCg));
    if (!p_QmCg)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("QM CG obj!!!"));
        return NULL;
    }
    memset(p_QmCg, 0, sizeof(t_QmCg));

    /* build CG struct */
    p_QmCg->h_Qm        = p_CgParams->h_Qm;
    p_QmCg->h_QmPortal  = p_QmPortal;
    p_QmCg->h_App       = p_CgParams->h_App;
    err = QmGetCgId(p_CgParams->h_Qm, &p_QmCg->id);
    if (err)
    {
        XX_Free(p_QmCg);
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("QmGetCgId failed"));
        return NULL;
    }

    NCSW_PLOCK(p_QmPortal);
    p_Mcc = qm_mc_start(p_QmPortal->p_LowQmPortal);
    p_Mcc->initcgr.cgid = p_QmCg->id;

    err = QmPortalRegisterCg(p_QmPortal, p_QmCg, p_QmCg->id);
    if (err)
    {
        XX_Free(p_QmCg);
        PUNLOCK(p_QmPortal);
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("QmPortalRegisterCg failed"));
        return NULL;
    }

    /*  Build CGR command */
    {
#ifdef QM_CGS_NO_FRAME_MODE
    t_QmRevisionInfo    revInfo;

    QmGetRevision(p_QmCg->h_Qm, &revInfo);

    if (!((revInfo.majorRev == 1) && (revInfo.minorRev == 0)))
#endif /* QM_CGS_NO_FRAME_MODE */
        if (p_CgParams->frameCount)
        {
            p_Mcc->initcgr.we_mask |= QM_CGR_WE_MODE;
            p_Mcc->initcgr.cgr.frame_mode = QM_CGR_EN;
        }
    }

    if (p_CgParams->wredEnable)
    {
        if (p_CgParams->wredParams.enableGreen)
        {
            err = CalcWredCurve(&p_CgParams->wredParams.greenCurve, &wredParams);
            if(err)
            {
                XX_Free(p_QmCg);
                PUNLOCK(p_QmPortal);
                REPORT_ERROR(MAJOR, err, NO_MSG);
                return NULL;
            }
            p_Mcc->initcgr.we_mask |= QM_CGR_WE_WR_EN_G | QM_CGR_WE_WR_PARM_G;
            p_Mcc->initcgr.cgr.wr_en_g = QM_CGR_EN;
            p_Mcc->initcgr.cgr.wr_parm_g.word = wredParams;
        }
        if (p_CgParams->wredParams.enableYellow)
        {
            err = CalcWredCurve(&p_CgParams->wredParams.yellowCurve, &wredParams);
            if(err)
            {
                XX_Free(p_QmCg);
                PUNLOCK(p_QmPortal);
                REPORT_ERROR(MAJOR, err, NO_MSG);
                return NULL;
            }
            p_Mcc->initcgr.we_mask |= QM_CGR_WE_WR_EN_Y | QM_CGR_WE_WR_PARM_Y;
            p_Mcc->initcgr.cgr.wr_en_y = QM_CGR_EN;
            p_Mcc->initcgr.cgr.wr_parm_y.word = wredParams;
        }
        if (p_CgParams->wredParams.enableRed)
        {
            err = CalcWredCurve(&p_CgParams->wredParams.redCurve, &wredParams);
            if(err)
            {
                XX_Free(p_QmCg);
                PUNLOCK(p_QmPortal);
                REPORT_ERROR(MAJOR, err, NO_MSG);
                return NULL;
            }
            p_Mcc->initcgr.we_mask |= QM_CGR_WE_WR_EN_R | QM_CGR_WE_WR_PARM_R;
            p_Mcc->initcgr.cgr.wr_en_r = QM_CGR_EN;
            p_Mcc->initcgr.cgr.wr_parm_r.word = wredParams;
        }
    }

    if (p_CgParams->tailDropEnable)
    {
        if (!p_CgParams->threshold)
        {
            XX_Free(p_QmCg);
            PUNLOCK(p_QmPortal);
            REPORT_ERROR(MINOR, E_INVALID_STATE, ("tailDropThreshold must be configured if tailDropEnable "));
            return NULL;
        }
        p_Mcc->initcgr.cgr.cstd_en = QM_CGR_EN;
        p_Mcc->initcgr.we_mask |= QM_CGR_WE_CSTD_EN;
    }

    if (p_CgParams->threshold)
    {
        p_Mcc->initcgr.we_mask |= QM_CGR_WE_CS_THRES;
        p_QmCg->f_Exception = p_CgParams->f_Exception;
        if (p_QmCg->f_Exception || p_CgParams->notifyDcPortal)
        {
            p_Mcc->initcgr.cgr.cscn_en = QM_CGR_EN;
            p_Mcc->initcgr.we_mask |= QM_CGR_WE_CSCN_EN | QM_CGR_WE_CSCN_TARG;
            /* if SW - set target, if HW - if FM, set HW target, otherwize, set SW target */
            p_Mcc->initcgr.cgr.cscn_targ = 0;
            if (p_QmCg->f_Exception)
                p_Mcc->initcgr.cgr.cscn_targ = (uint32_t)QM_CGR_TARGET_SWP(QmPortalGetSwPortalId(p_QmCg->h_QmPortal));
            if (p_CgParams->notifyDcPortal)
                p_Mcc->initcgr.cgr.cscn_targ |= (uint32_t)QM_CGR_TARGET_DCP(p_CgParams->dcPortalId);
        }

        /* express thresh as ta*2^tn */
        gap = (int)p_CgParams->threshold;
        for (tmpA=0 ; tmpA<256; tmpA++ )
            for (tmpN=0 ; tmpN<32; tmpN++ )
            {
                tmp = ABS((int)(p_CgParams->threshold - tmpA*(1<<tmpN)));
                if (tmp < gap)
                {
                   ta = tmpA;
                   tn = tmpN;
                   gap = tmp;
                }
            }
        p_Mcc->initcgr.cgr.cs_thres.TA = ta;
        p_Mcc->initcgr.cgr.cs_thres.Tn = tn;
    }
    else if(p_CgParams->f_Exception)
    {
        XX_Free(p_QmCg);
        PUNLOCK(p_QmPortal);
        REPORT_ERROR(MINOR, E_INVALID_STATE, ("No threshold configured, but f_Exception defined"));
        return NULL;
    }

    qm_mc_commit(p_QmPortal->p_LowQmPortal, QM_MCC_VERB_INITCGR);
    while (!(p_Mcr = qm_mc_result(p_QmPortal->p_LowQmPortal))) ;
    ASSERT_COND((p_Mcr->verb & QM_MCR_VERB_MASK) == QM_MCC_VERB_INITCGR);
    if (p_Mcr->result != QM_MCR_RESULT_OK)
    {
        XX_Free(p_QmCg);
        PUNLOCK(p_QmPortal);
        REPORT_ERROR(MINOR, E_INVALID_STATE, ("INITCGR failed: %s", mcr_result_str(p_Mcr->result)));
        return NULL;
    }
    PUNLOCK(p_QmPortal);

    return p_QmCg;
}