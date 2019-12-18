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
struct TYPE_3__ {int /*<<< orphan*/  f_FM_MAC_MII_ReadPhyReg; int /*<<< orphan*/  f_FM_MAC_MII_WritePhyReg; int /*<<< orphan*/  f_FM_MAC_GetMaxFrameLength; int /*<<< orphan*/ * f_FM_MAC_GetVersion; int /*<<< orphan*/  f_FM_MAC_GetId; int /*<<< orphan*/  f_FM_MAC_RemovelExactMatchMacAddr; int /*<<< orphan*/  f_FM_MAC_AddExactMatchMacAddr; int /*<<< orphan*/  f_FM_MAC_RemoveHashMacAddr; int /*<<< orphan*/  f_FM_MAC_AddHashMacAddr; int /*<<< orphan*/  f_FM_MAC_ModifyMacAddr; int /*<<< orphan*/  f_FM_MAC_GetStatistics; int /*<<< orphan*/  f_FM_MAC_ResetCounters; int /*<<< orphan*/  f_FM_MAC_SetWakeOnLan; int /*<<< orphan*/  f_FM_MAC_SetRxIgnorePauseFrames; int /*<<< orphan*/  f_FM_MAC_SetTxPauseFrames; int /*<<< orphan*/  f_FM_MAC_SetTxAutoPauseFrames; int /*<<< orphan*/  f_FM_MAC_Resume; int /*<<< orphan*/  f_FM_MAC_Disable; int /*<<< orphan*/  f_FM_MAC_Enable; int /*<<< orphan*/ * f_FM_MAC_RestartAutoneg; int /*<<< orphan*/  f_FM_MAC_AdjustLink; int /*<<< orphan*/  f_FM_MAC_SetPromiscuous; int /*<<< orphan*/ * f_FM_MAC_Disable1588TimeStamp; int /*<<< orphan*/  f_FM_MAC_Enable1588TimeStamp; int /*<<< orphan*/  f_FM_MAC_SetException; int /*<<< orphan*/  f_FM_MAC_ConfigResetOnInit; int /*<<< orphan*/  f_FM_MAC_ConfigException; int /*<<< orphan*/  f_FM_MAC_ConfigLengthCheck; int /*<<< orphan*/ * f_FM_MAC_ConfigHalfDuplex; int /*<<< orphan*/  f_FM_MAC_ConfigPadAndCrc; int /*<<< orphan*/  f_FM_MAC_ConfigWan; int /*<<< orphan*/  f_FM_MAC_ConfigMaxFrameLength; int /*<<< orphan*/  f_FM_MAC_ConfigLoopback; int /*<<< orphan*/ * f_FM_MAC_SetStatistics; int /*<<< orphan*/  f_FM_MAC_Free; int /*<<< orphan*/  f_FM_MAC_Init; } ;
typedef  TYPE_1__ t_FmMacControllerDriver ;

/* Variables and functions */
 int /*<<< orphan*/  MEMAC_MII_ReadPhyReg ; 
 int /*<<< orphan*/  MEMAC_MII_WritePhyReg ; 
 int /*<<< orphan*/  MemacAddExactMatchMacAddress ; 
 int /*<<< orphan*/  MemacAddHashMacAddress ; 
 int /*<<< orphan*/  MemacAdjustLink ; 
 int /*<<< orphan*/  MemacConfigException ; 
 int /*<<< orphan*/  MemacConfigLengthCheck ; 
 int /*<<< orphan*/  MemacConfigLoopback ; 
 int /*<<< orphan*/  MemacConfigMaxFrameLength ; 
 int /*<<< orphan*/  MemacConfigPad ; 
 int /*<<< orphan*/  MemacConfigResetOnInit ; 
 int /*<<< orphan*/  MemacConfigWan ; 
 int /*<<< orphan*/  MemacDelExactMatchMacAddress ; 
 int /*<<< orphan*/  MemacDelHashMacAddress ; 
 int /*<<< orphan*/  MemacDisable ; 
 int /*<<< orphan*/  MemacEnable ; 
 int /*<<< orphan*/  MemacEnable1588TimeStamp ; 
 int /*<<< orphan*/  MemacFree ; 
 int /*<<< orphan*/  MemacGetId ; 
 int /*<<< orphan*/  MemacGetMaxFrameLength ; 
 int /*<<< orphan*/  MemacGetStatistics ; 
 int /*<<< orphan*/  MemacInit ; 
 int /*<<< orphan*/  MemacInitInternalPhy ; 
 int /*<<< orphan*/  MemacModifyMacAddress ; 
 int /*<<< orphan*/  MemacResetCounters ; 
 int /*<<< orphan*/  MemacSetException ; 
 int /*<<< orphan*/  MemacSetPromiscuous ; 
 int /*<<< orphan*/  MemacSetRxIgnorePauseFrames ; 
 int /*<<< orphan*/  MemacSetTxAutoPauseFrames ; 
 int /*<<< orphan*/  MemacSetTxPauseFrames ; 
 int /*<<< orphan*/  MemacSetWakeOnLan ; 

__attribute__((used)) static void InitFmMacControllerDriver(t_FmMacControllerDriver *p_FmMacControllerDriver)
{
    p_FmMacControllerDriver->f_FM_MAC_Init                      = MemacInit;
    p_FmMacControllerDriver->f_FM_MAC_Free                      = MemacFree;

    p_FmMacControllerDriver->f_FM_MAC_SetStatistics             = NULL;
    p_FmMacControllerDriver->f_FM_MAC_ConfigLoopback            = MemacConfigLoopback;
    p_FmMacControllerDriver->f_FM_MAC_ConfigMaxFrameLength      = MemacConfigMaxFrameLength;

    p_FmMacControllerDriver->f_FM_MAC_ConfigWan                 = MemacConfigWan;

    p_FmMacControllerDriver->f_FM_MAC_ConfigPadAndCrc           = MemacConfigPad;
    p_FmMacControllerDriver->f_FM_MAC_ConfigHalfDuplex          = NULL; /* half-duplex is detected automatically */
    p_FmMacControllerDriver->f_FM_MAC_ConfigLengthCheck         = MemacConfigLengthCheck;

    p_FmMacControllerDriver->f_FM_MAC_ConfigException           = MemacConfigException;
    p_FmMacControllerDriver->f_FM_MAC_ConfigResetOnInit         = MemacConfigResetOnInit;

    p_FmMacControllerDriver->f_FM_MAC_SetException              = MemacSetException;

    p_FmMacControllerDriver->f_FM_MAC_Enable1588TimeStamp       = MemacEnable1588TimeStamp; /* always enabled */
    p_FmMacControllerDriver->f_FM_MAC_Disable1588TimeStamp      = NULL;

    p_FmMacControllerDriver->f_FM_MAC_SetPromiscuous            = MemacSetPromiscuous;
    p_FmMacControllerDriver->f_FM_MAC_AdjustLink                = MemacAdjustLink;
    p_FmMacControllerDriver->f_FM_MAC_RestartAutoneg            = NULL;

    p_FmMacControllerDriver->f_FM_MAC_Enable                    = MemacEnable;
    p_FmMacControllerDriver->f_FM_MAC_Disable                   = MemacDisable;
    p_FmMacControllerDriver->f_FM_MAC_Resume                    = MemacInitInternalPhy;

    p_FmMacControllerDriver->f_FM_MAC_SetTxAutoPauseFrames      = MemacSetTxAutoPauseFrames;
    p_FmMacControllerDriver->f_FM_MAC_SetTxPauseFrames          = MemacSetTxPauseFrames;
    p_FmMacControllerDriver->f_FM_MAC_SetRxIgnorePauseFrames    = MemacSetRxIgnorePauseFrames;

    p_FmMacControllerDriver->f_FM_MAC_SetWakeOnLan              = MemacSetWakeOnLan;

    p_FmMacControllerDriver->f_FM_MAC_ResetCounters             = MemacResetCounters;
    p_FmMacControllerDriver->f_FM_MAC_GetStatistics             = MemacGetStatistics;

    p_FmMacControllerDriver->f_FM_MAC_ModifyMacAddr             = MemacModifyMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_AddHashMacAddr            = MemacAddHashMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_RemoveHashMacAddr         = MemacDelHashMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_AddExactMatchMacAddr      = MemacAddExactMatchMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_RemovelExactMatchMacAddr  = MemacDelExactMatchMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_GetId                     = MemacGetId;
    p_FmMacControllerDriver->f_FM_MAC_GetVersion                = NULL;
    p_FmMacControllerDriver->f_FM_MAC_GetMaxFrameLength         = MemacGetMaxFrameLength;

    p_FmMacControllerDriver->f_FM_MAC_MII_WritePhyReg           = MEMAC_MII_WritePhyReg;
    p_FmMacControllerDriver->f_FM_MAC_MII_ReadPhyReg            = MEMAC_MII_ReadPhyReg;
}