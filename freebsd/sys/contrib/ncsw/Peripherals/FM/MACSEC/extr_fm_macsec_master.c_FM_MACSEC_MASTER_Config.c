#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_2__* t_Handle ;
typedef  int /*<<< orphan*/  t_FmMacsecRegs ;
struct TYPE_11__ {int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  baseAddr; int /*<<< orphan*/  h_FmMac; } ;
struct TYPE_13__ {TYPE_1__ nonGuestParams; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_3__ t_FmMacsecParams ;
struct TYPE_12__ {int byPassMode; struct TYPE_12__* p_FmMacsecDriverParam; int /*<<< orphan*/  h_Fm; struct TYPE_12__* fmMacsecModuleName; int /*<<< orphan*/  h_FmMac; int /*<<< orphan*/  mflSubtract; int /*<<< orphan*/  sectagOverhead; int /*<<< orphan*/  pnExhThr; int /*<<< orphan*/  reservedSc0; int /*<<< orphan*/  keysUnreadable; int /*<<< orphan*/  untagTreatMode; int /*<<< orphan*/  encryptWithNoChangedTextDiscardUncontrolled; int /*<<< orphan*/  invalidTagsDeliverUncontrolled; int /*<<< orphan*/  unknownSciTreatMode; void* txScSpinLock; void* rxScSpinLock; int /*<<< orphan*/  events; int /*<<< orphan*/  exceptions; int /*<<< orphan*/  userExceptions; int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/ * p_FmMacsecRegs; int /*<<< orphan*/  fmMacsecControllerDriver; } ;
typedef  TYPE_2__ t_FmMacsecDriverParam ;
typedef  TYPE_2__ t_FmMacsec ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_encryptWithNoChangedTextFrameTreatment ; 
 int /*<<< orphan*/  DEFAULT_events ; 
 int /*<<< orphan*/  DEFAULT_exceptions ; 
 int /*<<< orphan*/  DEFAULT_invalidTagsFrameTreatment ; 
 int /*<<< orphan*/  DEFAULT_keysUnreadable ; 
 int /*<<< orphan*/  DEFAULT_mflSubtract ; 
 int /*<<< orphan*/  DEFAULT_normalMode ; 
 int /*<<< orphan*/  DEFAULT_pnExhThr ; 
 int /*<<< orphan*/  DEFAULT_sc0ReservedForPTP ; 
 int /*<<< orphan*/  DEFAULT_sectagOverhead ; 
 int /*<<< orphan*/  DEFAULT_unknownSciFrameTreatment ; 
 int /*<<< orphan*/  DEFAULT_untagFrameTreatment ; 
 int /*<<< orphan*/  DEFAULT_userExceptions ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  FM_MAC_GetId (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FmGetId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitFmMacsecControllerDriver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 int MODULE_NAME_SIZE ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int Sprint (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 void* XX_InitSpinlock () ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_MACSEC_MASTER_Config(t_FmMacsecParams *p_FmMacsecParam)
{
    t_FmMacsec  *p_FmMacsec;
    uint32_t    macId;

    /* Allocate FM MACSEC structure */
    p_FmMacsec = (t_FmMacsec *) XX_Malloc(sizeof(t_FmMacsec));
    if (!p_FmMacsec)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM MACSEC driver structure"));
        return NULL;
    }
    memset(p_FmMacsec, 0, sizeof(t_FmMacsec));
    InitFmMacsecControllerDriver(&p_FmMacsec->fmMacsecControllerDriver);

    /* Allocate the FM MACSEC driver's parameters structure */
    p_FmMacsec->p_FmMacsecDriverParam = (t_FmMacsecDriverParam *)XX_Malloc(sizeof(t_FmMacsecDriverParam));
    if (!p_FmMacsec->p_FmMacsecDriverParam)
    {
        XX_Free(p_FmMacsec);
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM MACSEC driver parameters"));
        return NULL;
    }
    memset(p_FmMacsec->p_FmMacsecDriverParam, 0, sizeof(t_FmMacsecDriverParam));

    /* Initialize FM MACSEC parameters which will be kept by the driver */
    p_FmMacsec->h_Fm            = p_FmMacsecParam->h_Fm;
    p_FmMacsec->h_FmMac         = p_FmMacsecParam->nonGuestParams.h_FmMac;
    p_FmMacsec->p_FmMacsecRegs  = (t_FmMacsecRegs *)UINT_TO_PTR(p_FmMacsecParam->nonGuestParams.baseAddr);
    p_FmMacsec->f_Exception     = p_FmMacsecParam->nonGuestParams.f_Exception;
    p_FmMacsec->h_App           = p_FmMacsecParam->nonGuestParams.h_App;
    p_FmMacsec->userExceptions  = DEFAULT_userExceptions;
    p_FmMacsec->exceptions      = DEFAULT_exceptions;
    p_FmMacsec->events          = DEFAULT_events;
    p_FmMacsec->rxScSpinLock    = XX_InitSpinlock();
    p_FmMacsec->txScSpinLock    = XX_InitSpinlock();

    /* Initialize FM MACSEC driver parameters parameters (for initialization phase only) */
    p_FmMacsec->p_FmMacsecDriverParam->unknownSciTreatMode                           = DEFAULT_unknownSciFrameTreatment;
    p_FmMacsec->p_FmMacsecDriverParam->invalidTagsDeliverUncontrolled                = DEFAULT_invalidTagsFrameTreatment;
    p_FmMacsec->p_FmMacsecDriverParam->encryptWithNoChangedTextDiscardUncontrolled   = DEFAULT_encryptWithNoChangedTextFrameTreatment;
    p_FmMacsec->p_FmMacsecDriverParam->untagTreatMode                                = DEFAULT_untagFrameTreatment;
    p_FmMacsec->p_FmMacsecDriverParam->keysUnreadable                                = DEFAULT_keysUnreadable;
    p_FmMacsec->p_FmMacsecDriverParam->reservedSc0                                   = DEFAULT_sc0ReservedForPTP;
    p_FmMacsec->p_FmMacsecDriverParam->byPassMode                                    = !DEFAULT_normalMode;
    p_FmMacsec->p_FmMacsecDriverParam->pnExhThr                                      = DEFAULT_pnExhThr;
    p_FmMacsec->p_FmMacsecDriverParam->sectagOverhead                                = DEFAULT_sectagOverhead;
    p_FmMacsec->p_FmMacsecDriverParam->mflSubtract                                   = DEFAULT_mflSubtract;
    /* build the FM MACSEC master IPC address */
    memset(p_FmMacsec->fmMacsecModuleName, 0, (sizeof(char))*MODULE_NAME_SIZE);
    FM_MAC_GetId(p_FmMacsec->h_FmMac,&macId);
    if (Sprint (p_FmMacsec->fmMacsecModuleName, "FM-%d-MAC-%d-MACSEC-Master",
        FmGetId(p_FmMacsec->h_Fm),macId) != 24)
    {
        XX_Free(p_FmMacsec->p_FmMacsecDriverParam);
        XX_Free(p_FmMacsec);
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("Sprint failed"));
        return NULL;
    }
    return p_FmMacsec;
}