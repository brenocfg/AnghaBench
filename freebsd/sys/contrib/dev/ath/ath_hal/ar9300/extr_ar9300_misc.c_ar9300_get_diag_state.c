#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_7__ {int ah_nchan; } ;
struct TYPE_8__ {TYPE_2__ priv; int /*<<< orphan*/ * ah_channels; } ;
struct TYPE_10__ {int mrcCck; int /*<<< orphan*/  listenTime; int /*<<< orphan*/  cckNoiseImmunityLevel; int /*<<< orphan*/  ofdmWeakSigDetectOff; int /*<<< orphan*/  firstepLevel; int /*<<< orphan*/  spurImmunityLevel; int /*<<< orphan*/  noiseImmunityLevel; } ;
struct TYPE_6__ {scalar_t__ curr_step; } ;
struct ath_hal_9300 {int ah_pcdac_table_size; TYPE_3__ ah_priv; int /*<<< orphan*/  ah_ani_function; TYPE_5__ ext_ani_state; void* ah_pcdac_table; TYPE_1__ ah_gain_values; TYPE_4__* ah_mode_power_array2133; int /*<<< orphan*/  ah_eeprom; } ;
struct ath_hal {int dummy; } ;
typedef  void ar9300_ani_state ;
typedef  int /*<<< orphan*/  ar9300_eeprom_t ;
struct TYPE_9__ {int num_channels; void* p_channels; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  int /*<<< orphan*/  HAL_ANI_STATS ;
typedef  int /*<<< orphan*/  HAL_ANI_CMD ;
typedef  int /*<<< orphan*/  GAIN_VALUES ;
typedef  int /*<<< orphan*/  GAIN_OPTIMIZATION_STEP ;
typedef  int /*<<< orphan*/  EXPN_DATA_PER_CHANNEL_2133 ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 void* AH_NULL ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  HAL_ANI_ALL ; 
#define  HAL_DIAG_ANI_CMD 140 
#define  HAL_DIAG_ANI_CURRENT 139 
#define  HAL_DIAG_ANI_STATS 138 
#define  HAL_DIAG_CHANNELS 137 
#define  HAL_DIAG_EEPROM 136 
#define  HAL_DIAG_EEPROM_EXP_11A 135 
#define  HAL_DIAG_EEPROM_EXP_11B 134 
#define  HAL_DIAG_EEPROM_EXP_11G 133 
#define  HAL_DIAG_PCDAC 132 
#define  HAL_DIAG_PRINT_REG 131 
#define  HAL_DIAG_RFGAIN 130 
#define  HAL_DIAG_RFGAIN_CURSTEP 129 
#define  HAL_DIAG_TXCONT 128 
 int /*<<< orphan*/  ar9300_ani_control (struct ath_hal*,int const,int const) ; 
 void* ar9300_ani_get_current_state (struct ath_hal*) ; 
 void* ar9300_ani_get_current_stats (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_print_reg (struct ath_hal*,int const) ; 
 scalar_t__ ath_hal_getdiagstate (struct ath_hal*,int,void const*,int,void**,int*) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 TYPE_4__* pe ; 
 int /*<<< orphan*/  roundup (int,int) ; 

HAL_BOOL
ar9300_get_diag_state(struct ath_hal *ah, int request,
        const void *args, u_int32_t argsize,
        void **result, u_int32_t *resultsize)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    struct ar9300_ani_state *ani;

    (void) ahp;
    if (ath_hal_getdiagstate(ah, request, args, argsize, result, resultsize)) {
        return AH_TRUE;
    }
    switch (request) {
#ifdef AH_PRIVATE_DIAG
    case HAL_DIAG_EEPROM:
        *result = &ahp->ah_eeprom;
        *resultsize = sizeof(ar9300_eeprom_t);
        return AH_TRUE;

#if 0   /* XXX - TODO */
    case HAL_DIAG_EEPROM_EXP_11A:
    case HAL_DIAG_EEPROM_EXP_11B:
    case HAL_DIAG_EEPROM_EXP_11G:
        pe = &ahp->ah_mode_power_array2133[request - HAL_DIAG_EEPROM_EXP_11A];
        *result = pe->p_channels;
        *resultsize = (*result == AH_NULL) ? 0 :
            roundup(sizeof(u_int16_t) * pe->num_channels,
            sizeof(u_int32_t)) +
                sizeof(EXPN_DATA_PER_CHANNEL_2133) * pe->num_channels;
        return AH_TRUE;
#endif
    case HAL_DIAG_RFGAIN:
        *result = &ahp->ah_gain_values;
        *resultsize = sizeof(GAIN_VALUES);
        return AH_TRUE;
    case HAL_DIAG_RFGAIN_CURSTEP:
        *result = (void *) ahp->ah_gain_values.curr_step;
        *resultsize = (*result == AH_NULL) ?
                0 : sizeof(GAIN_OPTIMIZATION_STEP);
        return AH_TRUE;
#if 0   /* XXX - TODO */
    case HAL_DIAG_PCDAC:
        *result = ahp->ah_pcdac_table;
        *resultsize = ahp->ah_pcdac_table_size;
        return AH_TRUE;
#endif
    case HAL_DIAG_ANI_CURRENT:

        ani = ar9300_ani_get_current_state(ah);
        if (ani == AH_NULL)
            return AH_FALSE;
        /* Convert ar9300 HAL to FreeBSD HAL ANI state */
        bzero(&ahp->ext_ani_state, sizeof(ahp->ext_ani_state));
        ahp->ext_ani_state.noiseImmunityLevel = ani->ofdm_noise_immunity_level;
        ahp->ext_ani_state.spurImmunityLevel = ani->spur_immunity_level;
        ahp->ext_ani_state.firstepLevel = ani->firstep_level;
        ahp->ext_ani_state.ofdmWeakSigDetectOff = ani->ofdm_weak_sig_detect_off;
        ahp->ext_ani_state.mrcCck = !! ani->mrc_cck_off;
        ahp->ext_ani_state.cckNoiseImmunityLevel = ani->cck_noise_immunity_level;

        ahp->ext_ani_state.listenTime = ani->listen_time;

        *result = &ahp->ext_ani_state;
        *resultsize = sizeof(ahp->ext_ani_state);
#if 0
        *result = ar9300_ani_get_current_state(ah);
        *resultsize = (*result == AH_NULL) ?
            0 : sizeof(struct ar9300_ani_state);
#endif
        return AH_TRUE;
    case HAL_DIAG_ANI_STATS:
        *result = ar9300_ani_get_current_stats(ah);
        *resultsize = (*result == AH_NULL) ?
            0 : sizeof(HAL_ANI_STATS);
        return AH_TRUE;
    case HAL_DIAG_ANI_CMD:
    {
        HAL_ANI_CMD savefunc = ahp->ah_ani_function;
        if (argsize != 2*sizeof(u_int32_t)) {
            return AH_FALSE;
        }
        /* temporarly allow all functions so we can override */
        ahp->ah_ani_function = HAL_ANI_ALL;
        ar9300_ani_control(
            ah, ((const u_int32_t *)args)[0], ((const u_int32_t *)args)[1]);
        ahp->ah_ani_function = savefunc;
        return AH_TRUE;
    }
#if 0
    case HAL_DIAG_TXCONT:
        /*AR9300_CONTTXMODE(ah, (struct ath_desc *)args, argsize );*/
        return AH_TRUE;
#endif /* 0 */
#endif /* AH_PRIVATE_DIAG */
    case HAL_DIAG_CHANNELS:
#if 0
        *result = &(ahp->ah_priv.ah_channels[0]);
        *resultsize =
            sizeof(ahp->ah_priv.ah_channels[0]) * ahp->ah_priv.priv.ah_nchan;
#endif
        return AH_TRUE;
#ifdef AH_DEBUG
    case HAL_DIAG_PRINT_REG:
        ar9300_print_reg(ah, *((const u_int32_t *)args));
        return AH_TRUE;
#endif
    default:
        break;
    }

    return AH_FALSE;
}