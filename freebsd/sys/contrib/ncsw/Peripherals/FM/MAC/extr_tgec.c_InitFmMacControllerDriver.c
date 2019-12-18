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
struct TYPE_3__ {int /*<<< orphan*/  f_FM_MAC_MII_ReadPhyReg; int /*<<< orphan*/  f_FM_MAC_MII_WritePhyReg; int /*<<< orphan*/  f_FM_MAC_GetMaxFrameLength; int /*<<< orphan*/  f_FM_MAC_GetVersion; int /*<<< orphan*/  f_FM_MAC_GetId; int /*<<< orphan*/  f_FM_MAC_RemovelExactMatchMacAddr; int /*<<< orphan*/  f_FM_MAC_AddExactMatchMacAddr; int /*<<< orphan*/  f_FM_MAC_RemoveHashMacAddr; int /*<<< orphan*/  f_FM_MAC_AddHashMacAddr; int /*<<< orphan*/  f_FM_MAC_ModifyMacAddr; int /*<<< orphan*/  f_FM_MAC_GetStatistics; int /*<<< orphan*/  f_FM_MAC_ResetCounters; int /*<<< orphan*/  f_FM_MAC_SetRxIgnorePauseFrames; int /*<<< orphan*/  f_FM_MAC_SetTxPauseFrames; int /*<<< orphan*/  f_FM_MAC_SetTxAutoPauseFrames; int /*<<< orphan*/ * f_FM_MAC_Resume; int /*<<< orphan*/  f_FM_MAC_Disable; int /*<<< orphan*/  f_FM_MAC_Enable; int /*<<< orphan*/ * f_FM_MAC_RestartAutoneg; int /*<<< orphan*/ * f_FM_MAC_SetWakeOnLan; int /*<<< orphan*/ * f_FM_MAC_AdjustLink; int /*<<< orphan*/  f_FM_MAC_SetPromiscuous; int /*<<< orphan*/  f_FM_MAC_Disable1588TimeStamp; int /*<<< orphan*/  f_FM_MAC_Enable1588TimeStamp; int /*<<< orphan*/  f_FM_MAC_SetException; int /*<<< orphan*/  f_FM_MAC_ConfigSkipFman11Workaround; int /*<<< orphan*/ * f_FM_MAC_ConfigResetOnInit; int /*<<< orphan*/  f_FM_MAC_ConfigException; int /*<<< orphan*/  f_FM_MAC_ConfigLengthCheck; int /*<<< orphan*/ * f_FM_MAC_ConfigHalfDuplex; int /*<<< orphan*/ * f_FM_MAC_ConfigPadAndCrc; int /*<<< orphan*/  f_FM_MAC_ConfigWan; int /*<<< orphan*/  f_FM_MAC_ConfigMaxFrameLength; int /*<<< orphan*/  f_FM_MAC_ConfigLoopback; int /*<<< orphan*/ * f_FM_MAC_SetStatistics; int /*<<< orphan*/  f_FM_MAC_Free; int /*<<< orphan*/  f_FM_MAC_Init; } ;
typedef  TYPE_1__ t_FmMacControllerDriver ;

/* Variables and functions */
 int /*<<< orphan*/  TGEC_MII_ReadPhyReg ; 
 int /*<<< orphan*/  TGEC_MII_WritePhyReg ; 
 int /*<<< orphan*/  TgecAddExactMatchMacAddress ; 
 int /*<<< orphan*/  TgecAddHashMacAddress ; 
 int /*<<< orphan*/  TgecConfigException ; 
 int /*<<< orphan*/  TgecConfigLengthCheck ; 
 int /*<<< orphan*/  TgecConfigLoopback ; 
 int /*<<< orphan*/  TgecConfigMaxFrameLength ; 
 int /*<<< orphan*/  TgecConfigSkipFman11Workaround ; 
 int /*<<< orphan*/  TgecConfigWan ; 
 int /*<<< orphan*/  TgecDelExactMatchMacAddress ; 
 int /*<<< orphan*/  TgecDelHashMacAddress ; 
 int /*<<< orphan*/  TgecDisable ; 
 int /*<<< orphan*/  TgecDisable1588TimeStamp ; 
 int /*<<< orphan*/  TgecEnable ; 
 int /*<<< orphan*/  TgecEnable1588TimeStamp ; 
 int /*<<< orphan*/  TgecFree ; 
 int /*<<< orphan*/  TgecGetId ; 
 int /*<<< orphan*/  TgecGetMaxFrameLength ; 
 int /*<<< orphan*/  TgecGetStatistics ; 
 int /*<<< orphan*/  TgecGetVersion ; 
 int /*<<< orphan*/  TgecInit ; 
 int /*<<< orphan*/  TgecModifyMacAddress ; 
 int /*<<< orphan*/  TgecResetCounters ; 
 int /*<<< orphan*/  TgecRxIgnoreMacPause ; 
 int /*<<< orphan*/  TgecSetExcpetion ; 
 int /*<<< orphan*/  TgecSetPromiscuous ; 
 int /*<<< orphan*/  TgecSetTxPauseFrames ; 
 int /*<<< orphan*/  TgecTxMacPause ; 

__attribute__((used)) static void InitFmMacControllerDriver(t_FmMacControllerDriver *p_FmMacControllerDriver)
{
    p_FmMacControllerDriver->f_FM_MAC_Init                      = TgecInit;
    p_FmMacControllerDriver->f_FM_MAC_Free                      = TgecFree;

    p_FmMacControllerDriver->f_FM_MAC_SetStatistics             = NULL;
    p_FmMacControllerDriver->f_FM_MAC_ConfigLoopback            = TgecConfigLoopback;
    p_FmMacControllerDriver->f_FM_MAC_ConfigMaxFrameLength      = TgecConfigMaxFrameLength;

    p_FmMacControllerDriver->f_FM_MAC_ConfigWan                 = TgecConfigWan;

    p_FmMacControllerDriver->f_FM_MAC_ConfigPadAndCrc           = NULL; /* TGEC always works with pad+crc */
    p_FmMacControllerDriver->f_FM_MAC_ConfigHalfDuplex          = NULL; /* half-duplex is not supported in xgec */
    p_FmMacControllerDriver->f_FM_MAC_ConfigLengthCheck         = TgecConfigLengthCheck;
    p_FmMacControllerDriver->f_FM_MAC_ConfigException           = TgecConfigException;
    p_FmMacControllerDriver->f_FM_MAC_ConfigResetOnInit         = NULL;

#ifdef FM_TX_ECC_FRMS_ERRATA_10GMAC_A004
    p_FmMacControllerDriver->f_FM_MAC_ConfigSkipFman11Workaround= TgecConfigSkipFman11Workaround;
#endif /* FM_TX_ECC_FRMS_ERRATA_10GMAC_A004 */

    p_FmMacControllerDriver->f_FM_MAC_SetException              = TgecSetExcpetion;

    p_FmMacControllerDriver->f_FM_MAC_Enable1588TimeStamp       = TgecEnable1588TimeStamp;
    p_FmMacControllerDriver->f_FM_MAC_Disable1588TimeStamp      = TgecDisable1588TimeStamp;

    p_FmMacControllerDriver->f_FM_MAC_SetPromiscuous            = TgecSetPromiscuous;
    p_FmMacControllerDriver->f_FM_MAC_AdjustLink                = NULL;
    p_FmMacControllerDriver->f_FM_MAC_SetWakeOnLan              = NULL;
    p_FmMacControllerDriver->f_FM_MAC_RestartAutoneg            = NULL;

    p_FmMacControllerDriver->f_FM_MAC_Enable                    = TgecEnable;
    p_FmMacControllerDriver->f_FM_MAC_Disable                   = TgecDisable;
    p_FmMacControllerDriver->f_FM_MAC_Resume                    = NULL;

    p_FmMacControllerDriver->f_FM_MAC_SetTxAutoPauseFrames      = TgecTxMacPause;
    p_FmMacControllerDriver->f_FM_MAC_SetTxPauseFrames          = TgecSetTxPauseFrames;
    p_FmMacControllerDriver->f_FM_MAC_SetRxIgnorePauseFrames    = TgecRxIgnoreMacPause;

    p_FmMacControllerDriver->f_FM_MAC_ResetCounters             = TgecResetCounters;
    p_FmMacControllerDriver->f_FM_MAC_GetStatistics             = TgecGetStatistics;

    p_FmMacControllerDriver->f_FM_MAC_ModifyMacAddr             = TgecModifyMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_AddHashMacAddr            = TgecAddHashMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_RemoveHashMacAddr         = TgecDelHashMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_AddExactMatchMacAddr      = TgecAddExactMatchMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_RemovelExactMatchMacAddr  = TgecDelExactMatchMacAddress;
    p_FmMacControllerDriver->f_FM_MAC_GetId                     = TgecGetId;
    p_FmMacControllerDriver->f_FM_MAC_GetVersion                = TgecGetVersion;
    p_FmMacControllerDriver->f_FM_MAC_GetMaxFrameLength         = TgecGetMaxFrameLength;

    p_FmMacControllerDriver->f_FM_MAC_MII_WritePhyReg           = TGEC_MII_WritePhyReg;
    p_FmMacControllerDriver->f_FM_MAC_MII_ReadPhyReg            = TGEC_MII_ReadPhyReg;
}