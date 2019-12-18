#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
typedef  int int32_t ;
struct TYPE_9__ {int misc_configuration; int feature_enable; int txrx_mask; } ;
struct TYPE_10__ {int temp_slope_low; int temp_slope_high; } ;
struct TYPE_12__ {int* tempslopextension; } ;
struct TYPE_11__ {int temp_slope; } ;
struct TYPE_8__ {int temp_slope; } ;
struct TYPE_13__ {TYPE_2__ base_eep_header; TYPE_3__ base_ext2; TYPE_5__ base_ext1; TYPE_4__ modal_header_5g; int /*<<< orphan*/ * cal_freq_pier_5g; TYPE_1__ modal_header_2g; } ;
typedef  TYPE_6__ ar9300_eeprom_t ;
struct TYPE_14__ {TYPE_6__ ah_eeprom; } ;

/* Variables and functions */
 TYPE_7__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B0 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B2 ; 
 int /*<<< orphan*/  AR_PHY_TPC_18 ; 
 int /*<<< orphan*/  AR_PHY_TPC_18_THERM_CAL_VALUE ; 
 int /*<<< orphan*/  AR_PHY_TPC_19 ; 
 int /*<<< orphan*/  AR_PHY_TPC_19_ALPHA_THERM ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_B0 ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_B1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_B2 ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_ERROR_EST_MODE ; 
 int AR_PHY_TPC_6_ERROR_EST_MODE_S ; 
 int /*<<< orphan*/  AR_PHY_TPC_OLPC_GAIN_DELTA ; 
 int AR_PHY_TPC_OLPC_GAIN_DELTA_S ; 
 int /*<<< orphan*/  AR_SCORPION_PHY_TPC_19_B1 ; 
 int /*<<< orphan*/  AR_SCORPION_PHY_TPC_19_B2 ; 
 int /*<<< orphan*/  AR_SREV_HONEYBEE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_JUPITER (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_POSEIDON (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_SCORPION (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_WASP (struct ath_hal*) ; 
 int FBIN2FREQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int interpolate (int,int*,int*,int) ; 

int
ar9300_power_control_override(struct ath_hal *ah, int frequency,
    int *correction, int *voltage, int *temperature)
{
    int temp_slope = 0;
    int temp_slope_1 = 0;
    int temp_slope_2 = 0;
    ar9300_eeprom_t *eep = &AH9300(ah)->ah_eeprom;
    int32_t f[8], t[8],t1[3], t2[3];
	int i;

    OS_REG_RMW(ah, AR_PHY_TPC_11_B0,
        (correction[0] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
        AR_PHY_TPC_OLPC_GAIN_DELTA);
    if (!AR_SREV_POSEIDON(ah)) {
        OS_REG_RMW(ah, AR_PHY_TPC_11_B1,
            (correction[1] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
            AR_PHY_TPC_OLPC_GAIN_DELTA);
        if (!AR_SREV_WASP(ah) && !AR_SREV_JUPITER(ah) && !AR_SREV_HONEYBEE(ah) ) {
            OS_REG_RMW(ah, AR_PHY_TPC_11_B2, 
                (correction[2] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
                AR_PHY_TPC_OLPC_GAIN_DELTA);
        }
    }
    /*
     * enable open loop power control on chip
     */
    OS_REG_RMW(ah, AR_PHY_TPC_6_B0,
        (3 << AR_PHY_TPC_6_ERROR_EST_MODE_S), AR_PHY_TPC_6_ERROR_EST_MODE);
    if (!AR_SREV_POSEIDON(ah)) {
        OS_REG_RMW(ah, AR_PHY_TPC_6_B1, 
            (3 << AR_PHY_TPC_6_ERROR_EST_MODE_S), AR_PHY_TPC_6_ERROR_EST_MODE);
        if (!AR_SREV_WASP(ah) && !AR_SREV_JUPITER(ah) && !AR_SREV_HONEYBEE(ah)  ) {
            OS_REG_RMW(ah, AR_PHY_TPC_6_B2, 
                (3 << AR_PHY_TPC_6_ERROR_EST_MODE_S),
                AR_PHY_TPC_6_ERROR_EST_MODE);
        }
    }

    /*
     * Enable temperature compensation
     * Need to use register names
     */
    if (frequency < 4000) {
        temp_slope = eep->modal_header_2g.temp_slope;
    } else {
		if ((eep->base_eep_header.misc_configuration & 0x20) != 0)
		{
				for(i=0;i<8;i++)
				{
					t[i]=eep->base_ext1.tempslopextension[i];
					f[i]=FBIN2FREQ(eep->cal_freq_pier_5g[i], 0);
				}
				temp_slope=interpolate(frequency,f,t,8);
		}
		else
		{
        if(!AR_SREV_SCORPION(ah)) {
          if (eep->base_ext2.temp_slope_low != 0) {
             t[0] = eep->base_ext2.temp_slope_low;
             f[0] = 5180;
             t[1] = eep->modal_header_5g.temp_slope;
             f[1] = 5500;
             t[2] = eep->base_ext2.temp_slope_high;
             f[2] = 5785;
             temp_slope = interpolate(frequency, f, t, 3);
           } else {
             temp_slope = eep->modal_header_5g.temp_slope;
           }
         } else {
            /*
             * Scorpion has individual chain tempslope values
             */
             t[0] = eep->base_ext1.tempslopextension[2];
             t1[0]= eep->base_ext1.tempslopextension[3];
             t2[0]= eep->base_ext1.tempslopextension[4];
             f[0] = 5180;
             t[1] = eep->modal_header_5g.temp_slope;
             t1[1]= eep->base_ext1.tempslopextension[0];
             t2[1]= eep->base_ext1.tempslopextension[1];
             f[1] = 5500;
             t[2] = eep->base_ext1.tempslopextension[5];
             t1[2]= eep->base_ext1.tempslopextension[6];
             t2[2]= eep->base_ext1.tempslopextension[7];
             f[2] = 5785;
             temp_slope = interpolate(frequency, f, t, 3);
             temp_slope_1=interpolate(frequency, f, t1,3);
             temp_slope_2=interpolate(frequency, f, t2,3);
       } 
	 }
  }

    if (!AR_SREV_SCORPION(ah) && !AR_SREV_HONEYBEE(ah)) {
        OS_REG_RMW_FIELD(ah,
            AR_PHY_TPC_19, AR_PHY_TPC_19_ALPHA_THERM, temp_slope);
    } else {
        /*Scorpion and Honeybee has tempSlope register for each chain*/
        /*Check whether temp_compensation feature is enabled or not*/
        if (eep->base_eep_header.feature_enable & 0x1){
	    if(frequency < 4000) {
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x1) {
		    OS_REG_RMW_FIELD(ah,
				    AR_PHY_TPC_19, AR_PHY_TPC_19_ALPHA_THERM, 
				    eep->base_ext2.temp_slope_low);
		    } 
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x2) {
		    OS_REG_RMW_FIELD(ah,
				    AR_SCORPION_PHY_TPC_19_B1, AR_PHY_TPC_19_ALPHA_THERM, 
				    temp_slope);
		    } 
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x4) {
		    OS_REG_RMW_FIELD(ah,
				    AR_SCORPION_PHY_TPC_19_B2, AR_PHY_TPC_19_ALPHA_THERM, 
				    eep->base_ext2.temp_slope_high);
		     } 	
	    } else {
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x1) {
		    OS_REG_RMW_FIELD(ah,
				    AR_PHY_TPC_19, AR_PHY_TPC_19_ALPHA_THERM, 
				    temp_slope);
			}
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x2) {
		    OS_REG_RMW_FIELD(ah,
				    AR_SCORPION_PHY_TPC_19_B1, AR_PHY_TPC_19_ALPHA_THERM, 
				    temp_slope_1);
		}
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x4) {
		    OS_REG_RMW_FIELD(ah,
				    AR_SCORPION_PHY_TPC_19_B2, AR_PHY_TPC_19_ALPHA_THERM, 
				    temp_slope_2);
			} 
	    }
        }else {
        	/* If temp compensation is not enabled, set all registers to 0*/
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x1) {
            OS_REG_RMW_FIELD(ah,
                AR_PHY_TPC_19, AR_PHY_TPC_19_ALPHA_THERM, 0);
		    }
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x2) {
            OS_REG_RMW_FIELD(ah,
                AR_SCORPION_PHY_TPC_19_B1, AR_PHY_TPC_19_ALPHA_THERM, 0);
		    }  
		if (((eep->base_eep_header.txrx_mask & 0xf0) >> 4) & 0x4) {
            OS_REG_RMW_FIELD(ah,
                AR_SCORPION_PHY_TPC_19_B2, AR_PHY_TPC_19_ALPHA_THERM, 0);
		} 
        }
    }
    OS_REG_RMW_FIELD(ah,
        AR_PHY_TPC_18, AR_PHY_TPC_18_THERM_CAL_VALUE, temperature[0]);

    return 0;
}