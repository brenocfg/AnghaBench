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
struct TYPE_3__ {int /*<<< orphan*/  f_FM_MACSEC_SetException; int /*<<< orphan*/  f_FM_MACSEC_Disable; int /*<<< orphan*/  f_FM_MACSEC_Enable; int /*<<< orphan*/  f_FM_MACSEC_GetRevision; int /*<<< orphan*/  f_FM_MACSEC_ConfigException; int /*<<< orphan*/  f_FM_MACSEC_ConfigSectagWithoutSCI; int /*<<< orphan*/  f_FM_MACSEC_ConfigKeysUnreadable; int /*<<< orphan*/  f_FM_MACSEC_ConfigPnExhaustionThreshold; int /*<<< orphan*/  f_FM_MACSEC_ConfigOnlyScbIsSetFrameTreatment; int /*<<< orphan*/  f_FM_MACSEC_ConfigChangedTextWithNoEncryptFrameTreatment; int /*<<< orphan*/  f_FM_MACSEC_ConfigUntagFrameTreatment; int /*<<< orphan*/  f_FM_MACSEC_ConfigEncryptWithNoChangedTextFrameTreatment; int /*<<< orphan*/  f_FM_MACSEC_ConfigInvalidTagsFrameTreatment; int /*<<< orphan*/  f_FM_MACSEC_ConfigUnknownSciFrameTreatment; int /*<<< orphan*/  f_FM_MACSEC_Free; int /*<<< orphan*/  f_FM_MACSEC_Init; } ;
typedef  TYPE_1__ t_FmMacsecControllerDriver ;

/* Variables and functions */
 int /*<<< orphan*/  MacsecConfigChangedTextWithNoEncryptFrameTreatment ; 
 int /*<<< orphan*/  MacsecConfigEncryptWithNoChangedTextFrameTreatment ; 
 int /*<<< orphan*/  MacsecConfigException ; 
 int /*<<< orphan*/  MacsecConfigInvalidTagsFrameTreatment ; 
 int /*<<< orphan*/  MacsecConfigKeysUnreadable ; 
 int /*<<< orphan*/  MacsecConfigOnlyScbIsSetFrameTreatment ; 
 int /*<<< orphan*/  MacsecConfigPnExhaustionThreshold ; 
 int /*<<< orphan*/  MacsecConfigSectagWithoutSCI ; 
 int /*<<< orphan*/  MacsecConfigUnknownSciFrameTreatment ; 
 int /*<<< orphan*/  MacsecConfigUntagFrameTreatment ; 
 int /*<<< orphan*/  MacsecDisable ; 
 int /*<<< orphan*/  MacsecEnable ; 
 int /*<<< orphan*/  MacsecFree ; 
 int /*<<< orphan*/  MacsecGetRevision ; 
 int /*<<< orphan*/  MacsecInit ; 
 int /*<<< orphan*/  MacsecSetException ; 

__attribute__((used)) static void InitFmMacsecControllerDriver(t_FmMacsecControllerDriver *p_FmMacsecControllerDriver)
{
    p_FmMacsecControllerDriver->f_FM_MACSEC_Init                                            = MacsecInit;
    p_FmMacsecControllerDriver->f_FM_MACSEC_Free                                            = MacsecFree;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigUnknownSciFrameTreatment                  = MacsecConfigUnknownSciFrameTreatment;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigInvalidTagsFrameTreatment                 = MacsecConfigInvalidTagsFrameTreatment;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigEncryptWithNoChangedTextFrameTreatment    = MacsecConfigEncryptWithNoChangedTextFrameTreatment;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigUntagFrameTreatment                       = MacsecConfigUntagFrameTreatment;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigChangedTextWithNoEncryptFrameTreatment    = MacsecConfigChangedTextWithNoEncryptFrameTreatment;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigOnlyScbIsSetFrameTreatment                = MacsecConfigOnlyScbIsSetFrameTreatment;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigPnExhaustionThreshold                     = MacsecConfigPnExhaustionThreshold;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigKeysUnreadable                            = MacsecConfigKeysUnreadable;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigSectagWithoutSCI                          = MacsecConfigSectagWithoutSCI;
    p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigException                                 = MacsecConfigException;
    p_FmMacsecControllerDriver->f_FM_MACSEC_GetRevision                                     = MacsecGetRevision;
    p_FmMacsecControllerDriver->f_FM_MACSEC_Enable                                          = MacsecEnable;
    p_FmMacsecControllerDriver->f_FM_MACSEC_Disable                                         = MacsecDisable;
    p_FmMacsecControllerDriver->f_FM_MACSEC_SetException                                    = MacsecSetException;
}