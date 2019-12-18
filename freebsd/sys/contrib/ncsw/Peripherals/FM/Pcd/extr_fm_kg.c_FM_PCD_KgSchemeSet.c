#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/ * t_Handle ;
struct TYPE_22__ {int /*<<< orphan*/  update; } ;
struct TYPE_20__ {size_t relativeSchemeId; int /*<<< orphan*/ * h_Scheme; } ;
struct TYPE_23__ {scalar_t__ modify; TYPE_3__ schemeCounter; TYPE_1__ id; } ;
typedef  TYPE_4__ t_FmPcdKgSchemeParams ;
struct TYPE_24__ {size_t schemeId; scalar_t__ p_Lock; TYPE_6__* h_FmPcd; } ;
typedef  TYPE_5__ t_FmPcdKgScheme ;
struct TYPE_25__ {size_t numOfSchemes; size_t* schemesIds; struct TYPE_25__* p_FmPcdKg; TYPE_2__* p_IndirectAccessRegs; scalar_t__ h_Hc; TYPE_5__* schemes; } ;
typedef  TYPE_6__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
struct fman_kg_scheme_regs {int /*<<< orphan*/ * kgse_gec; int /*<<< orphan*/  kgse_vsp; int /*<<< orphan*/  kgse_om; int /*<<< orphan*/  kgse_fqb; int /*<<< orphan*/  kgse_spc; int /*<<< orphan*/  kgse_hc; int /*<<< orphan*/  kgse_bmcl; int /*<<< orphan*/  kgse_bmch; int /*<<< orphan*/  kgse_ekfc; int /*<<< orphan*/  kgse_ekdv; int /*<<< orphan*/  kgse_dv1; int /*<<< orphan*/  kgse_dv0; int /*<<< orphan*/  kgse_mv; int /*<<< orphan*/  kgse_mode; int /*<<< orphan*/  kgse_ccbs; int /*<<< orphan*/  kgse_ppc; } ;
struct TYPE_21__ {struct fman_kg_scheme_regs schemeRegs; } ;

/* Variables and functions */
 scalar_t__ BuildSchemeRegs (int /*<<< orphan*/ *,TYPE_4__*,struct fman_kg_scheme_regs*) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ E_ALREADY_EXISTS ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_NOT_AVAILABLE ; 
 scalar_t__ E_NOT_IN_RANGE ; 
 scalar_t__ E_OK ; 
 size_t FM_KG_NUM_OF_GENERIC_REGS ; 
 scalar_t__ FmHcPcdKgSetScheme (scalar_t__,int /*<<< orphan*/ *,struct fman_kg_scheme_regs*,int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdAcquireLock (TYPE_6__*) ; 
 int /*<<< orphan*/  FmPcdKgBuildWriteSchemeActionReg (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdKgIsSchemeValidSw (TYPE_5__*) ; 
 int /*<<< orphan*/  FmPcdReleaseLock (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  KgHwLock (TYPE_6__*) ; 
 int /*<<< orphan*/  KgHwUnlock (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KgSchemeFlagTryLock (TYPE_5__*) ; 
 int /*<<< orphan*/  KgSchemeFlagUnlock (TYPE_5__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  ValidateSchemeSw (TYPE_5__*) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteKgarWait (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_PCD_KgSchemeSet(t_Handle h_FmPcd,  t_FmPcdKgSchemeParams *p_SchemeParams)
{
    t_FmPcd                             *p_FmPcd;
    struct fman_kg_scheme_regs          schemeRegs;
    struct fman_kg_scheme_regs          *p_MemRegs;
    uint8_t                             i;
    t_Error                             err = E_OK;
    uint32_t                            tmpKgarReg;
    uint32_t                            intFlags;
    uint8_t                             physicalSchemeId, relativeSchemeId = 0;
    t_FmPcdKgScheme                     *p_Scheme;

    if (p_SchemeParams->modify)
    {
        p_Scheme = (t_FmPcdKgScheme *)p_SchemeParams->id.h_Scheme;
        p_FmPcd = p_Scheme->h_FmPcd;

        SANITY_CHECK_RETURN_VALUE(p_FmPcd, E_INVALID_HANDLE, NULL);
        SANITY_CHECK_RETURN_VALUE(p_FmPcd->p_FmPcdKg, E_INVALID_HANDLE, NULL);

        if (!FmPcdKgIsSchemeValidSw(p_Scheme))
        {
            REPORT_ERROR(MAJOR, E_ALREADY_EXISTS,
                         ("Scheme is invalid"));
            return NULL;
        }

        if (!KgSchemeFlagTryLock(p_Scheme))
        {
            DBG(TRACE, ("Scheme Try Lock - BUSY"));
            /* Signal to caller BUSY condition */
            p_SchemeParams->id.h_Scheme = NULL;
            return NULL;
        }
    }
    else
    {
        p_FmPcd = (t_FmPcd*)h_FmPcd;

        SANITY_CHECK_RETURN_VALUE(p_FmPcd, E_INVALID_HANDLE, NULL);
        SANITY_CHECK_RETURN_VALUE(p_FmPcd->p_FmPcdKg, E_INVALID_HANDLE, NULL);

        relativeSchemeId = p_SchemeParams->id.relativeSchemeId;
        /* check that schemeId is in range */
        if (relativeSchemeId >= p_FmPcd->p_FmPcdKg->numOfSchemes)
        {
            REPORT_ERROR(MAJOR, E_NOT_IN_RANGE, ("relative-scheme-id %d!", relativeSchemeId));
            return NULL;
        }

        p_Scheme = &p_FmPcd->p_FmPcdKg->schemes[relativeSchemeId];
        if (FmPcdKgIsSchemeValidSw(p_Scheme))
        {
            REPORT_ERROR(MAJOR, E_ALREADY_EXISTS,
                         ("Scheme id (%d)!", relativeSchemeId));
            return NULL;
        }
        /* Clear all fields, scheme may have beed previously used */
        memset(p_Scheme, 0, sizeof(t_FmPcdKgScheme));

        p_Scheme->schemeId = p_FmPcd->p_FmPcdKg->schemesIds[relativeSchemeId];
        p_Scheme->h_FmPcd = p_FmPcd;

        p_Scheme->p_Lock = FmPcdAcquireLock(p_FmPcd);
        if (!p_Scheme->p_Lock)
            REPORT_ERROR(MAJOR, E_NOT_AVAILABLE, ("FM KG Scheme lock obj!"));
    }

    err = BuildSchemeRegs((t_Handle)p_Scheme, p_SchemeParams, &schemeRegs);
    if (err)
    {
        REPORT_ERROR(MAJOR, err, NO_MSG);
        if (p_SchemeParams->modify)
            KgSchemeFlagUnlock(p_Scheme);
        if (!p_SchemeParams->modify &&
            p_Scheme->p_Lock)
            FmPcdReleaseLock(p_FmPcd, p_Scheme->p_Lock);
        return NULL;
    }

    if (p_FmPcd->h_Hc)
    {
        err = FmHcPcdKgSetScheme(p_FmPcd->h_Hc,
                                 (t_Handle)p_Scheme,
                                 &schemeRegs,
                                 p_SchemeParams->schemeCounter.update);
        if (p_SchemeParams->modify)
            KgSchemeFlagUnlock(p_Scheme);
        if (err)
        {
            if (!p_SchemeParams->modify &&
                p_Scheme->p_Lock)
                FmPcdReleaseLock(p_FmPcd, p_Scheme->p_Lock);
            return NULL;
        }
        if (!p_SchemeParams->modify)
            ValidateSchemeSw(p_Scheme);
        return (t_Handle)p_Scheme;
    }

    physicalSchemeId = p_Scheme->schemeId;

    /* configure all 21 scheme registers */
    p_MemRegs = &p_FmPcd->p_FmPcdKg->p_IndirectAccessRegs->schemeRegs;
    intFlags = KgHwLock(p_FmPcd->p_FmPcdKg);
    WRITE_UINT32(p_MemRegs->kgse_ppc,   schemeRegs.kgse_ppc);
    WRITE_UINT32(p_MemRegs->kgse_ccbs,  schemeRegs.kgse_ccbs);
    WRITE_UINT32(p_MemRegs->kgse_mode,  schemeRegs.kgse_mode);
    WRITE_UINT32(p_MemRegs->kgse_mv,    schemeRegs.kgse_mv);
    WRITE_UINT32(p_MemRegs->kgse_dv0,   schemeRegs.kgse_dv0);
    WRITE_UINT32(p_MemRegs->kgse_dv1,   schemeRegs.kgse_dv1);
    WRITE_UINT32(p_MemRegs->kgse_ekdv,  schemeRegs.kgse_ekdv);
    WRITE_UINT32(p_MemRegs->kgse_ekfc,  schemeRegs.kgse_ekfc);
    WRITE_UINT32(p_MemRegs->kgse_bmch,  schemeRegs.kgse_bmch);
    WRITE_UINT32(p_MemRegs->kgse_bmcl,  schemeRegs.kgse_bmcl);
    WRITE_UINT32(p_MemRegs->kgse_hc,    schemeRegs.kgse_hc);
    WRITE_UINT32(p_MemRegs->kgse_spc,   schemeRegs.kgse_spc);
    WRITE_UINT32(p_MemRegs->kgse_fqb,   schemeRegs.kgse_fqb);
    WRITE_UINT32(p_MemRegs->kgse_om,    schemeRegs.kgse_om);
    WRITE_UINT32(p_MemRegs->kgse_vsp,   schemeRegs.kgse_vsp);
    for (i=0 ; i<FM_KG_NUM_OF_GENERIC_REGS ; i++)
        WRITE_UINT32(p_MemRegs->kgse_gec[i], schemeRegs.kgse_gec[i]);

    /* call indirect command for scheme write */
    tmpKgarReg = FmPcdKgBuildWriteSchemeActionReg(physicalSchemeId, p_SchemeParams->schemeCounter.update);

    WriteKgarWait(p_FmPcd, tmpKgarReg);
    KgHwUnlock(p_FmPcd->p_FmPcdKg, intFlags);

    if (!p_SchemeParams->modify)
        ValidateSchemeSw(p_Scheme);
    else
        KgSchemeFlagUnlock(p_Scheme);

    return (t_Handle)p_Scheme;
}