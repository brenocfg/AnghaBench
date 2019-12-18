#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {int fmpl_pects; int fmpl_pepts_ets; scalar_t__ fmpl_perrpc; scalar_t__ fmpl_perypc; scalar_t__ fmpl_perpc; scalar_t__ fmpl_peypc; scalar_t__ fmpl_pegpc; scalar_t__ fmpl_pernia; scalar_t__ fmpl_peynia; scalar_t__ fmpl_pegnia; scalar_t__ fmpl_pemode; scalar_t__ fmpl_pepbs_ebs; scalar_t__ fmpl_pepepir_eir; scalar_t__ fmpl_pecbs; scalar_t__ fmpl_pecir; int /*<<< orphan*/  fmpl_pelts; } ;
typedef  TYPE_3__ t_FmPcdPlcrProfileRegs ;
struct TYPE_13__ {int /*<<< orphan*/  rollBackFrameSelection; int /*<<< orphan*/  frameLengthSelection; } ;
struct TYPE_17__ {TYPE_2__ byteModeParams; int /*<<< orphan*/  rateMode; int /*<<< orphan*/  peakOrExcessInfoRate; int /*<<< orphan*/  committedInfoRate; } ;
struct TYPE_12__ {int /*<<< orphan*/  override; int /*<<< orphan*/  dfltColor; } ;
struct TYPE_15__ {int algSelection; TYPE_7__ nonPassthroughAlgParams; TYPE_1__ color; int /*<<< orphan*/  colorMode; int /*<<< orphan*/  paramsOnRed; int /*<<< orphan*/  nextEngineOnRed; int /*<<< orphan*/  paramsOnYellow; int /*<<< orphan*/  nextEngineOnYellow; int /*<<< orphan*/  paramsOnGreen; int /*<<< orphan*/  nextEngineOnGreen; } ;
typedef  TYPE_4__ t_FmPcdPlcrProfileParams ;
struct TYPE_16__ {int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_5__*) ; 
 int /*<<< orphan*/  CalcRates (scalar_t__,TYPE_7__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ E_INVALID_SELECTION ; 
 scalar_t__ E_NOT_AVAILABLE ; 
 scalar_t__ E_OK ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_ALG_MASK ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_ALG_RFC2698 ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_ALG_RFC4115 ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_CBLND ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_DEFC_MASK ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_DEFC_OVERRIDE ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_DEFC_R ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_DEFC_Y ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_FLS_FULL ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_FLS_L2 ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_FLS_L3 ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_FLS_L4 ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_FPP_SHIFT ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_OVCLR_G_NC ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_OVCLR_MASK ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_OVCLR_R ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_OVCLR_Y ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_PI ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_PKT ; 
 scalar_t__ FM_PCD_PLCR_PEMODE_RBFLS ; 
 scalar_t__ FmGetTimeStampScale (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ SetProfileNia (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
#define  e_FM_PCD_PLCR_BYTE_MODE 144 
#define  e_FM_PCD_PLCR_COLOR_AWARE 143 
#define  e_FM_PCD_PLCR_COLOR_BLIND 142 
#define  e_FM_PCD_PLCR_FULL_FRM_LEN 141 
#define  e_FM_PCD_PLCR_GREEN 140 
#define  e_FM_PCD_PLCR_L2_FRM_LEN 139 
#define  e_FM_PCD_PLCR_L3_FRM_LEN 138 
#define  e_FM_PCD_PLCR_L4_FRM_LEN 137 
#define  e_FM_PCD_PLCR_OVERRIDE 136 
#define  e_FM_PCD_PLCR_PACKET_MODE 135 
#define  e_FM_PCD_PLCR_PASS_THROUGH 134 
#define  e_FM_PCD_PLCR_RED 133 
#define  e_FM_PCD_PLCR_RFC_2698 132 
#define  e_FM_PCD_PLCR_RFC_4115 131 
#define  e_FM_PCD_PLCR_ROLLBACK_FULL_FRM_LEN 130 
#define  e_FM_PCD_PLCR_ROLLBACK_L2_FRM_LEN 129 
#define  e_FM_PCD_PLCR_YELLOW 128 

__attribute__((used)) static t_Error BuildProfileRegs(t_FmPcd                     *p_FmPcd,
                                t_FmPcdPlcrProfileParams    *p_ProfileParams,
                                t_FmPcdPlcrProfileRegs      *p_PlcrRegs)
{
    t_Error                 err = E_OK;
    uint32_t                pemode, gnia, ynia, rnia, bitFor1Micro;

    ASSERT_COND(p_FmPcd);

    bitFor1Micro = FmGetTimeStampScale(p_FmPcd->h_Fm);
    if (bitFor1Micro == 0)
    RETURN_ERROR(MAJOR, E_NOT_AVAILABLE, ("Timestamp scale"));

/* Set G, Y, R Nia */
    err = SetProfileNia(p_FmPcd, p_ProfileParams->nextEngineOnGreen,  &(p_ProfileParams->paramsOnGreen), &gnia);
    if (err)
        RETURN_ERROR(MAJOR, err, NO_MSG);
    err = SetProfileNia(p_FmPcd, p_ProfileParams->nextEngineOnYellow, &(p_ProfileParams->paramsOnYellow), &ynia);
    if (err)
        RETURN_ERROR(MAJOR, err, NO_MSG);
    err = SetProfileNia(p_FmPcd, p_ProfileParams->nextEngineOnRed,    &(p_ProfileParams->paramsOnRed), &rnia);
   if (err)
        RETURN_ERROR(MAJOR, err, NO_MSG);

/* Mode fmpl_pemode */
    pemode = FM_PCD_PLCR_PEMODE_PI;

    switch (p_ProfileParams->algSelection)
    {
        case    e_FM_PCD_PLCR_PASS_THROUGH:
            p_PlcrRegs->fmpl_pecir         = 0;
            p_PlcrRegs->fmpl_pecbs         = 0;
            p_PlcrRegs->fmpl_pepepir_eir   = 0;
            p_PlcrRegs->fmpl_pepbs_ebs     = 0;
            p_PlcrRegs->fmpl_pelts         = 0;
            p_PlcrRegs->fmpl_pects         = 0;
            p_PlcrRegs->fmpl_pepts_ets     = 0;
            pemode &= ~FM_PCD_PLCR_PEMODE_ALG_MASK;
            switch (p_ProfileParams->colorMode)
            {
                case    e_FM_PCD_PLCR_COLOR_BLIND:
                    pemode |= FM_PCD_PLCR_PEMODE_CBLND;
                    switch (p_ProfileParams->color.dfltColor)
                    {
                        case e_FM_PCD_PLCR_GREEN:
                            pemode &= ~FM_PCD_PLCR_PEMODE_DEFC_MASK;
                            break;
                        case e_FM_PCD_PLCR_YELLOW:
                            pemode |= FM_PCD_PLCR_PEMODE_DEFC_Y;
                            break;
                        case e_FM_PCD_PLCR_RED:
                            pemode |= FM_PCD_PLCR_PEMODE_DEFC_R;
                            break;
                        case e_FM_PCD_PLCR_OVERRIDE:
                            pemode |= FM_PCD_PLCR_PEMODE_DEFC_OVERRIDE;
                            break;
                        default:
                            RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
                    }

                    break;
                case    e_FM_PCD_PLCR_COLOR_AWARE:
                    pemode &= ~FM_PCD_PLCR_PEMODE_CBLND;
                    break;
                default:
                    RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
            }
            break;

        case    e_FM_PCD_PLCR_RFC_2698:
            /* Select algorithm MODE[ALG] = "01" */
            pemode |= FM_PCD_PLCR_PEMODE_ALG_RFC2698;
            if (p_ProfileParams->nonPassthroughAlgParams.committedInfoRate > p_ProfileParams->nonPassthroughAlgParams.peakOrExcessInfoRate)
                RETURN_ERROR(MAJOR, E_INVALID_SELECTION, ("in RFC2698 Peak rate must be equal or larger than committedInfoRate."));
            goto cont_rfc;
        case    e_FM_PCD_PLCR_RFC_4115:
            /* Select algorithm MODE[ALG] = "10" */
            pemode |= FM_PCD_PLCR_PEMODE_ALG_RFC4115;
cont_rfc:
            /* Select Color-Blind / Color-Aware operation (MODE[CBLND]) */
            switch (p_ProfileParams->colorMode)
            {
                case    e_FM_PCD_PLCR_COLOR_BLIND:
                    pemode |= FM_PCD_PLCR_PEMODE_CBLND;
                    break;
                case    e_FM_PCD_PLCR_COLOR_AWARE:
                    pemode &= ~FM_PCD_PLCR_PEMODE_CBLND;
                    /*In color aware more select override color interpretation (MODE[OVCLR]) */
                    switch (p_ProfileParams->color.override)
                    {
                        case e_FM_PCD_PLCR_GREEN:
                            pemode &= ~FM_PCD_PLCR_PEMODE_OVCLR_MASK;
                            break;
                        case e_FM_PCD_PLCR_YELLOW:
                            pemode |= FM_PCD_PLCR_PEMODE_OVCLR_Y;
                            break;
                        case e_FM_PCD_PLCR_RED:
                            pemode |= FM_PCD_PLCR_PEMODE_OVCLR_R;
                            break;
                        case e_FM_PCD_PLCR_OVERRIDE:
                            pemode |= FM_PCD_PLCR_PEMODE_OVCLR_G_NC;
                            break;
                        default:
                            RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
                    }
                    break;
                default:
                    RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
            }
            /* Select Measurement Unit Mode to BYTE or PACKET (MODE[PKT]) */
            switch (p_ProfileParams->nonPassthroughAlgParams.rateMode)
            {
                case e_FM_PCD_PLCR_BYTE_MODE :
                    pemode &= ~FM_PCD_PLCR_PEMODE_PKT;
                        switch (p_ProfileParams->nonPassthroughAlgParams.byteModeParams.frameLengthSelection)
                        {
                            case e_FM_PCD_PLCR_L2_FRM_LEN:
                                pemode |= FM_PCD_PLCR_PEMODE_FLS_L2;
                                break;
                            case e_FM_PCD_PLCR_L3_FRM_LEN:
                                pemode |= FM_PCD_PLCR_PEMODE_FLS_L3;
                                break;
                            case e_FM_PCD_PLCR_L4_FRM_LEN:
                                pemode |= FM_PCD_PLCR_PEMODE_FLS_L4;
                                break;
                            case e_FM_PCD_PLCR_FULL_FRM_LEN:
                                pemode |= FM_PCD_PLCR_PEMODE_FLS_FULL;
                                break;
                            default:
                                RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
                        }
                        switch (p_ProfileParams->nonPassthroughAlgParams.byteModeParams.rollBackFrameSelection)
                        {
                            case e_FM_PCD_PLCR_ROLLBACK_L2_FRM_LEN:
                                pemode &= ~FM_PCD_PLCR_PEMODE_RBFLS;
                                break;
                            case e_FM_PCD_PLCR_ROLLBACK_FULL_FRM_LEN:
                                pemode |= FM_PCD_PLCR_PEMODE_RBFLS;
                                break;
                            default:
                                RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
                        }
                    break;
                case e_FM_PCD_PLCR_PACKET_MODE :
                    pemode |= FM_PCD_PLCR_PEMODE_PKT;
                    break;
                default:
                    RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
            }
            /* Select timeStamp floating point position (MODE[FPP]) to fit the actual traffic rates. For PACKET
               mode with low traffic rates move the fixed point to the left to increase fraction accuracy. For BYTE
               mode with high traffic rates move the fixed point to the right to increase integer accuracy. */

            /* Configure Traffic Parameters*/
            {
                uint32_t cir=0, cbs=0, pir_eir=0, pbs_ebs=0, fpp=0;

                CalcRates(bitFor1Micro, &p_ProfileParams->nonPassthroughAlgParams, &cir, &cbs, &pir_eir, &pbs_ebs, &fpp);

                /*  Set Committed Information Rate (CIR) */
                p_PlcrRegs->fmpl_pecir = cir;
                /*  Set Committed Burst Size (CBS). */
                p_PlcrRegs->fmpl_pecbs =  cbs;
                /*  Set Peak Information Rate (PIR_EIR used as PIR) */
                p_PlcrRegs->fmpl_pepepir_eir = pir_eir;
                /*   Set Peak Burst Size (PBS_EBS used as PBS) */
                p_PlcrRegs->fmpl_pepbs_ebs = pbs_ebs;

                /* Initialize the Metering Buckets to be full (write them with 0xFFFFFFFF. */
                /* Peak Rate Token Bucket Size (PTS_ETS used as PTS) */
                p_PlcrRegs->fmpl_pepts_ets = 0xFFFFFFFF;
                /* Committed Rate Token Bucket Size (CTS) */
                p_PlcrRegs->fmpl_pects = 0xFFFFFFFF;

                /* Set the FPP based on calculation */
                pemode |= (fpp << FM_PCD_PLCR_PEMODE_FPP_SHIFT);
            }
            break;  /* FM_PCD_PLCR_PEMODE_ALG_RFC2698 , FM_PCD_PLCR_PEMODE_ALG_RFC4115 */
        default:
            RETURN_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
    }

    p_PlcrRegs->fmpl_pemode = pemode;

    p_PlcrRegs->fmpl_pegnia = gnia;
    p_PlcrRegs->fmpl_peynia = ynia;
    p_PlcrRegs->fmpl_pernia = rnia;

    /* Zero Counters */
    p_PlcrRegs->fmpl_pegpc     = 0;
    p_PlcrRegs->fmpl_peypc     = 0;
    p_PlcrRegs->fmpl_perpc     = 0;
    p_PlcrRegs->fmpl_perypc    = 0;
    p_PlcrRegs->fmpl_perrpc    = 0;

    return E_OK;
}