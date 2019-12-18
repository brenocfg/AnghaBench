#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {scalar_t__ h_Profile; int /*<<< orphan*/  h_DirectScheme; int /*<<< orphan*/  action; } ;
typedef  TYPE_1__ u_FmPcdPlcrNextEngineParams ;
struct TYPE_5__ {int absoluteProfileId; } ;
typedef  TYPE_2__ t_FmPcdPlcrProfile ;
typedef  int /*<<< orphan*/  t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int e_FmPcdEngine ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_SELECTION ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NOT_IN_RANGE ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_PCD_KG_NUM_OF_SCHEMES ; 
 int FM_PCD_PLCR_NIA_VALID ; 
 int FmPcdKgGetRelativeSchemeId (int /*<<< orphan*/ *,int) ; 
 int FmPcdKgGetSchemeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdKgIsSchemeValidSw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdPlcrIsProfileValid (int /*<<< orphan*/ *,int) ; 
 int GET_NIA_BMI_AC_DISCARD_FRAME (int /*<<< orphan*/ *) ; 
 int GET_NIA_BMI_AC_ENQ_FRAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsProfileShared (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  KgIsSchemeAlwaysDirect (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAJOR ; 
 int NIA_ENG_KG ; 
 int NIA_ENG_PLCR ; 
 int NIA_KG_DIRECT ; 
 int NIA_PLCR_ABSOLUTE ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  e_FM_PCD_DONE 132 
#define  e_FM_PCD_DROP_FRAME 131 
#define  e_FM_PCD_ENQ_FRAME 130 
#define  e_FM_PCD_KG 129 
#define  e_FM_PCD_PLCR 128 

__attribute__((used)) static t_Error SetProfileNia(t_FmPcd *p_FmPcd, e_FmPcdEngine nextEngine, u_FmPcdPlcrNextEngineParams *p_NextEngineParams, uint32_t *nextAction)
{
    uint32_t    nia;
    uint16_t    absoluteProfileId;
    uint8_t     relativeSchemeId, physicalSchemeId;

    nia = FM_PCD_PLCR_NIA_VALID;

    switch (nextEngine)
    {
        case e_FM_PCD_DONE :
            switch (p_NextEngineParams->action)
            {
                case e_FM_PCD_DROP_FRAME :
                    nia |= GET_NIA_BMI_AC_DISCARD_FRAME(p_FmPcd);
                    break;
                case e_FM_PCD_ENQ_FRAME:
                    nia |= GET_NIA_BMI_AC_ENQ_FRAME(p_FmPcd);
                    break;
                default:
                    RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
            }
            break;
        case e_FM_PCD_KG:
            physicalSchemeId = FmPcdKgGetSchemeId(p_NextEngineParams->h_DirectScheme);
            relativeSchemeId = FmPcdKgGetRelativeSchemeId(p_FmPcd, physicalSchemeId);
            if (relativeSchemeId >= FM_PCD_KG_NUM_OF_SCHEMES)
                RETURN_ERROR(MAJOR, E_NOT_IN_RANGE, NO_MSG);
            if (!FmPcdKgIsSchemeValidSw(p_NextEngineParams->h_DirectScheme))
                RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Invalid direct scheme."));
            if (!KgIsSchemeAlwaysDirect(p_FmPcd, relativeSchemeId))
                RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Policer Profile may point only to a scheme that is always direct."));
            nia |= NIA_ENG_KG | NIA_KG_DIRECT | physicalSchemeId;
            break;
        case e_FM_PCD_PLCR:
            absoluteProfileId = ((t_FmPcdPlcrProfile *)p_NextEngineParams->h_Profile)->absoluteProfileId;
            if (!IsProfileShared(p_FmPcd, absoluteProfileId))
                RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Next profile must be a shared profile"));
            if (!FmPcdPlcrIsProfileValid(p_FmPcd, absoluteProfileId))
                RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Invalid profile "));
            nia |= NIA_ENG_PLCR | NIA_PLCR_ABSOLUTE | absoluteProfileId;
            break;
        default:
            RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
    }

    *nextAction =  nia;

    return E_OK;
}