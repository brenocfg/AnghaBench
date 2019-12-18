#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* t_Handle ;
typedef  int /*<<< orphan*/  t_FmMacsecSecYSCParams ;
struct TYPE_10__ {int /*<<< orphan*/  txScParams; int /*<<< orphan*/  numReceiveChannels; int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  h_FmMacsec; } ;
typedef  TYPE_2__ t_FmMacsecSecYParams ;
struct TYPE_9__ {int /*<<< orphan*/  txScParams; struct TYPE_9__* p_FmMacsecSecYDriverParam; int /*<<< orphan*/  events; int /*<<< orphan*/  exceptions; int /*<<< orphan*/  numOfTxSc; int /*<<< orphan*/  numOfRxSc; int /*<<< orphan*/  isPointToPoint; int /*<<< orphan*/  sciInsertionMode; int /*<<< orphan*/  protectFrames; int /*<<< orphan*/  replayWindow; int /*<<< orphan*/  replayProtect; int /*<<< orphan*/  validateFrames; int /*<<< orphan*/  confidentialityOffset; int /*<<< orphan*/  confidentialityEnable; int /*<<< orphan*/  h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  h_FmMacsec; } ;
typedef  TYPE_1__ t_FmMacsecSecYDriverParam ;
typedef  TYPE_1__ t_FmMacsecSecY ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_confidentialityEnable ; 
 int /*<<< orphan*/  DEFAULT_confidentialityOffset ; 
 int /*<<< orphan*/  DEFAULT_events ; 
 int /*<<< orphan*/  DEFAULT_exceptions ; 
 int /*<<< orphan*/  DEFAULT_numOfTxSc ; 
 int /*<<< orphan*/  DEFAULT_protectFrames ; 
 int /*<<< orphan*/  DEFAULT_ptp ; 
 int /*<<< orphan*/  DEFAULT_replayEnable ; 
 int /*<<< orphan*/  DEFAULT_replayWindow ; 
 int /*<<< orphan*/  DEFAULT_sciInsertionMode ; 
 int /*<<< orphan*/  DEFAULT_validateFrames ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_MACSEC_SECY_Config(t_FmMacsecSecYParams *p_FmMacsecSecYParam)
{
    t_FmMacsecSecY  *p_FmMacsecSecY;

    /* Allocate FM MACSEC structure */
    p_FmMacsecSecY = (t_FmMacsecSecY *) XX_Malloc(sizeof(t_FmMacsecSecY));
    if (!p_FmMacsecSecY)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM MACSEC SECY driver structure"));
        return NULL;
    }
    memset(p_FmMacsecSecY, 0, sizeof(t_FmMacsecSecY));

    /* Allocate the FM MACSEC driver's parameters structure */
    p_FmMacsecSecY->p_FmMacsecSecYDriverParam = (t_FmMacsecSecYDriverParam *)XX_Malloc(sizeof(t_FmMacsecSecYDriverParam));
    if (!p_FmMacsecSecY->p_FmMacsecSecYDriverParam)
    {
        XX_Free(p_FmMacsecSecY);
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("FM MACSEC SECY driver parameters"));
        return NULL;
    }
    memset(p_FmMacsecSecY->p_FmMacsecSecYDriverParam, 0, sizeof(t_FmMacsecSecYDriverParam));

    /* Initialize FM MACSEC SECY parameters which will be kept by the driver */
    p_FmMacsecSecY->h_FmMacsec              = p_FmMacsecSecYParam->h_FmMacsec;
    p_FmMacsecSecY->f_Event                 = p_FmMacsecSecYParam->f_Event;
    p_FmMacsecSecY->f_Exception             = p_FmMacsecSecYParam->f_Exception;
    p_FmMacsecSecY->h_App                   = p_FmMacsecSecYParam->h_App;
    p_FmMacsecSecY->confidentialityEnable   = DEFAULT_confidentialityEnable;
    p_FmMacsecSecY->confidentialityOffset   = DEFAULT_confidentialityOffset;
    p_FmMacsecSecY->validateFrames          = DEFAULT_validateFrames;
    p_FmMacsecSecY->replayProtect           = DEFAULT_replayEnable;
    p_FmMacsecSecY->replayWindow            = DEFAULT_replayWindow;
    p_FmMacsecSecY->protectFrames           = DEFAULT_protectFrames;
    p_FmMacsecSecY->sciInsertionMode        = DEFAULT_sciInsertionMode;
    p_FmMacsecSecY->isPointToPoint          = DEFAULT_ptp;
    p_FmMacsecSecY->numOfRxSc               = p_FmMacsecSecYParam->numReceiveChannels;
    p_FmMacsecSecY->numOfTxSc               = DEFAULT_numOfTxSc;
    p_FmMacsecSecY->exceptions              = DEFAULT_exceptions;
    p_FmMacsecSecY->events                  = DEFAULT_events;

    memcpy(&p_FmMacsecSecY->p_FmMacsecSecYDriverParam->txScParams,
           &p_FmMacsecSecYParam->txScParams,
           sizeof(t_FmMacsecSecYSCParams));
    return p_FmMacsecSecY;
}