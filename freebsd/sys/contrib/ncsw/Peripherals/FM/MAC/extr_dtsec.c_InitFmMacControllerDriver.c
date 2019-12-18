#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  f_FM_MAC_MII_ReadPhyReg; int /*<<< orphan*/  f_FM_MAC_MII_WritePhyReg; int /*<<< orphan*/  f_FM_MAC_GetMaxFrameLength; int /*<<< orphan*/  f_FM_MAC_GetVersion; int /*<<< orphan*/  f_FM_MAC_GetId; int /*<<< orphan*/  f_FM_MAC_RemovelExactMatchMacAddr; int /*<<< orphan*/  f_FM_MAC_AddExactMatchMacAddr; int /*<<< orphan*/  f_FM_MAC_RemoveHashMacAddr; int /*<<< orphan*/  f_FM_MAC_AddHashMacAddr; int /*<<< orphan*/  f_FM_MAC_ModifyMacAddr; int /*<<< orphan*/  f_FM_MAC_GetStatistics; int /*<<< orphan*/  f_FM_MAC_ResetCounters; int /*<<< orphan*/  f_FM_MAC_SetRxIgnorePauseFrames; int /*<<< orphan*/  f_FM_MAC_SetTxPauseFrames; int /*<<< orphan*/  f_FM_MAC_SetTxAutoPauseFrames; int /*<<< orphan*/  f_FM_MAC_Disable1588TimeStamp; int /*<<< orphan*/  f_FM_MAC_Enable1588TimeStamp; int /*<<< orphan*/  f_FM_MAC_RestartAutoneg; int /*<<< orphan*/  f_FM_MAC_SetWakeOnLan; int /*<<< orphan*/  f_FM_MAC_AdjustLink; int /*<<< orphan*/  f_FM_MAC_SetPromiscuous; int /*<<< orphan*/  f_FM_MAC_SetException; int /*<<< orphan*/ * f_FM_MAC_Resume; int /*<<< orphan*/  f_FM_MAC_Disable; int /*<<< orphan*/  f_FM_MAC_Enable; int /*<<< orphan*/ * f_FM_MAC_ConfigResetOnInit; int /*<<< orphan*/  f_FM_MAC_ConfigException; int /*<<< orphan*/  f_FM_MAC_ConfigTbiPhyAddr; int /*<<< orphan*/  f_FM_MAC_ConfigLengthCheck; int /*<<< orphan*/  f_FM_MAC_ConfigHalfDuplex; int /*<<< orphan*/  f_FM_MAC_ConfigPadAndCrc; int /*<<< orphan*/ * f_FM_MAC_ConfigWan; int /*<<< orphan*/  f_FM_MAC_ConfigMaxFrameLength; int /*<<< orphan*/  f_FM_MAC_ConfigLoopback; int /*<<< orphan*/  f_FM_MAC_SetStatistics; int /*<<< orphan*/  f_FM_MAC_Free; int /*<<< orphan*/  f_FM_MAC_Init; } ;
typedef  TYPE_1__ t_FmMacControllerDriver ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_MII_ReadPhyReg ; 
 int /*<<< orphan*/  DTSEC_MII_WritePhyReg ; 
 int /*<<< orphan*/  DtsecAddExactMatchMacAddress ; 
 int /*<<< orphan*/  DtsecAddHashMacAddress ; 
 int /*<<< orphan*/  DtsecAdjustLink ; 
 int /*<<< orphan*/  DtsecConfigException ; 
 int /*<<< orphan*/  DtsecConfigHalfDuplex ; 
 int /*<<< orphan*/  DtsecConfigLengthCheck ; 
 int /*<<< orphan*/  DtsecConfigLoopback ; 
 int /*<<< orphan*/  DtsecConfigMaxFrameLength ; 
 int /*<<< orphan*/  DtsecConfigPadAndCrc ; 
 int /*<<< orphan*/  DtsecConfigTbiPhyAddr ; 
 int /*<<< orphan*/  DtsecDelExactMatchMacAddress ; 
 int /*<<< orphan*/  DtsecDelHashMacAddress ; 
 int /*<<< orphan*/  DtsecDisable ; 
 int /*<<< orphan*/  DtsecDisable1588TimeStamp ; 
 int /*<<< orphan*/  DtsecEnable ; 
 int /*<<< orphan*/  DtsecEnable1588TimeStamp ; 
 int /*<<< orphan*/  DtsecFree ; 
 int /*<<< orphan*/  DtsecGetId ; 
 int /*<<< orphan*/  DtsecGetMaxFrameLength ; 
 int /*<<< orphan*/  DtsecGetStatistics ; 
 int /*<<< orphan*/  DtsecGetVersion ; 
 int /*<<< orphan*/  DtsecInit ; 
 int /*<<< orphan*/  DtsecModifyMacAddress ; 
 int /*<<< orphan*/  DtsecResetCounters ; 
 int /*<<< orphan*/  DtsecRestartAutoneg ; 
 int /*<<< orphan*/  DtsecRxIgnoreMacPause ; 
 int /*<<< orphan*/  DtsecSetException ; 
 int /*<<< orphan*/  DtsecSetPromiscuous ; 
 int /*<<< orphan*/  DtsecSetStatistics ; 
 int /*<<< orphan*/  DtsecSetTxPauseFrames ; 
 int /*<<< orphan*/  DtsecSetWakeOnLan ; 
 int /*<<< orphan*/  DtsecTxMacPause ; 

__attribute__((used)) static void InitFmMacControllerDriver(t_FmMacControllerDriver *p_FmMacControllerDriver)
{
    p_FmMacControllerDriver->f_FM_MAC_Init                      = DtsecInit;
    p_FmMacControllerDriver->f_FM_MAC_Free                      = DtsecFree;

    p_FmMacControllerDriver->f_FM_MAC_SetStatistics             = DtsecSetStatistics;
    p_FmMacControllerDriver->f_FM_MAC_ConfigLoopback            = DtsecConfigLoopback;
    p_FmMacControllerDriver->f_FM_MAC_ConfigMaxFrameLength      = DtsecConfigMaxFrameLength;

    p_FmMacControllerDriver->f_FM_MAC_ConfigWan                 = NULL; /* Not supported on dTSEC */

    p_FmMacControllerDriver->f_FM_MAC_ConfigPadAndCrc           = DtsecConfigPadAndCrc;
    p_FmMacControllerDriver->f_FM_MAC_ConfigHalfDuplex          = DtsecConfigHalfDuplex;
    p_FmMacControllerDriver->f_FM_MAC_ConfigLengthCheck         = DtsecConfigLengthCheck;
    p_FmMacControllerDriver->f_FM_MAC_ConfigTbiPhyAddr          = DtsecConfigTbiPhyAddr;
    p_FmMacControllerDriver->f_FM_MAC_ConfigException           = DtsecConfigException;
    p_FmMacControllerDriver->f_FM_MAC_ConfigResetOnInit         = NULL;

    p_FmMacControllerDriver->f_FM_MAC_Enable                    = DtsecEnable;
    p_FmMacControllerDriver->f_FM_MAC_Disable                   = DtsecDisable;
    p_FmMacControllerDriver->f_FM_MAC_Resume                    = NULL;

    p_FmMacControllerDriver->f_FM_MAC_SetException              = DtsecSetException;

    p_FmMacControllerDriver->f_FM_MAC_SetPromiscuous            = DtsecSetPromiscuous;
    p_FmMacControllerDriver->f_FM_MAC_AdjustLink                = DtsecAdjustLink;
    p_FmMacControllerDriver->f_FM_MAC_SetWakeOnLan              = DtsecSetWakeOnLan;
    p_FmMacControllerDriver->f_FM_MAC_RestartAutoneg            = DtsecRestartAutoneg;

    p_FmMacControllerDriver->f_FM_MAC_Enable1588TimeStamp       = DtsecEnable1588TimeStamp;
    p_FmMacControllerDriver->f_FM_MAC_Disable1588TimeStamp      = DtsecDisable1588TimeStamp;

    p_FmMacControllerDriver->f_FM_MAC_SetTxAutoPauseFrames      = DtsecTxMacPause;
    p_FmMacControllerDriver->f_FM_MAC_SetTxPauseFrames          = DtsecSetTxPauseFrames;
    p_FmMacControllerDriver->f_FM_MAC_SetRxIgnorePauseFrames    = DtsecRxIgnoreMacPause;

    p_FmMacControllerDriver->f_FM_MAC_ResetCounters             = DtsecResetCounters;
    p_FmMacControllerDriver->f_FM_MAC_GetStatistics             = DtsecGetStatistics;

    p_FmMacControllerDriver->f_FM_MAC_ModifyMacAddr             = DtsecModifyMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_AddHashMacAddr            = DtsecAddHashMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_RemoveHashMacAddr         = DtsecDelHashMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_AddExactMatchMacAddr      = DtsecAddExactMatchMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_RemovelExactMatchMacAddr  = DtsecDelExactMatchMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_GetId                     = DtsecGetId;
    p_FmMacControllerDriver->f_FM_MAC_GetVersion                = DtsecGetVersion;
    p_FmMacControllerDriver->f_FM_MAC_GetMaxFrameLength         = DtsecGetMaxFrameLength;

    p_FmMacControllerDriver->f_FM_MAC_MII_WritePhyReg           = DTSEC_MII_WritePhyReg;
    p_FmMacControllerDriver->f_FM_MAC_MII_ReadPhyReg            = DTSEC_MII_ReadPhyReg;

}