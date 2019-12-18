#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 size_t ALL_TARGET_HT20_0_8_16 ; 
 size_t ALL_TARGET_HT20_12 ; 
 size_t ALL_TARGET_HT20_13 ; 
 size_t ALL_TARGET_HT20_14 ; 
 size_t ALL_TARGET_HT20_15 ; 
 size_t ALL_TARGET_HT20_1_3_9_11_17_19 ; 
 size_t ALL_TARGET_HT20_20 ; 
 size_t ALL_TARGET_HT20_21 ; 
 size_t ALL_TARGET_HT20_22 ; 
 size_t ALL_TARGET_HT20_23 ; 
 size_t ALL_TARGET_HT20_4 ; 
 size_t ALL_TARGET_HT20_5 ; 
 size_t ALL_TARGET_HT20_6 ; 
 size_t ALL_TARGET_HT20_7 ; 
 size_t ALL_TARGET_HT40_0_8_16 ; 
 size_t ALL_TARGET_HT40_12 ; 
 size_t ALL_TARGET_HT40_13 ; 
 size_t ALL_TARGET_HT40_14 ; 
 size_t ALL_TARGET_HT40_15 ; 
 size_t ALL_TARGET_HT40_1_3_9_11_17_19 ; 
 size_t ALL_TARGET_HT40_20 ; 
 size_t ALL_TARGET_HT40_21 ; 
 size_t ALL_TARGET_HT40_22 ; 
 size_t ALL_TARGET_HT40_23 ; 
 size_t ALL_TARGET_HT40_4 ; 
 size_t ALL_TARGET_HT40_5 ; 
 size_t ALL_TARGET_HT40_6 ; 
 size_t ALL_TARGET_HT40_7 ; 
 size_t ALL_TARGET_LEGACY_11L ; 
 size_t ALL_TARGET_LEGACY_11S ; 
 size_t ALL_TARGET_LEGACY_1L_5L ; 
 size_t ALL_TARGET_LEGACY_36 ; 
 size_t ALL_TARGET_LEGACY_48 ; 
 size_t ALL_TARGET_LEGACY_54 ; 
 size_t ALL_TARGET_LEGACY_5S ; 
 size_t ALL_TARGET_LEGACY_6_24 ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int,int) ; 
 int POW_SM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  field_write (char*,int /*<<< orphan*/ ) ; 

int
ar9300_transmit_power_reg_write(struct ath_hal *ah, u_int8_t *p_pwr_array) 
{   
#define POW_SM(_r, _s)     (((_r) & 0x3f) << (_s))
    /* make sure forced gain is not set */
#if 0
    field_write("force_dac_gain", 0);
    OS_REG_WRITE(ah, 0xa3f8, 0);
    field_write("force_tx_gain", 0);
#endif

    OS_REG_WRITE(ah, 0xa458, 0);

    /* Write the OFDM power per rate set */
    /* 6 (LSB), 9, 12, 18 (MSB) */
    OS_REG_WRITE(ah, 0xa3c0,
        POW_SM(p_pwr_array[ALL_TARGET_LEGACY_6_24], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_6_24], 16)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_6_24],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_6_24],  0)
    );
    /* 24 (LSB), 36, 48, 54 (MSB) */
    OS_REG_WRITE(ah, 0xa3c4,
        POW_SM(p_pwr_array[ALL_TARGET_LEGACY_54], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_48], 16)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_36],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_6_24],  0)
    );

    /* Write the CCK power per rate set */
    /* 1L (LSB), reserved, 2L, 2S (MSB) */  
    OS_REG_WRITE(ah, 0xa3c8,
        POW_SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L],  16)
/*          | POW_SM(tx_power_times2,  8)*/ /* this is reserved for Osprey */
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L],   0)
    );
    /* 5.5L (LSB), 5.5S, 11L, 11S (MSB) */
    OS_REG_WRITE(ah, 0xa3cc,
        POW_SM(p_pwr_array[ALL_TARGET_LEGACY_11S], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_11L], 16)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_5S],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L],  0)
    );

	/* write the power for duplicated frames - HT40 */
	/* dup40_cck (LSB), dup40_ofdm, ext20_cck, ext20_ofdm  (MSB) */
    OS_REG_WRITE(ah, 0xa3e0,
        POW_SM(p_pwr_array[ALL_TARGET_LEGACY_6_24], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L], 16)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_6_24],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L],  0)
    );

    /* Write the HT20 power per rate set */
    /* 0/8/16 (LSB), 1-3/9-11/17-19, 4, 5 (MSB) */
    OS_REG_WRITE(ah, 0xa3d0,
        POW_SM(p_pwr_array[ALL_TARGET_HT20_5], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_4],  16)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_1_3_9_11_17_19],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_0_8_16],   0)
    );
    
    /* 6 (LSB), 7, 12, 13 (MSB) */
    OS_REG_WRITE(ah, 0xa3d4,
        POW_SM(p_pwr_array[ALL_TARGET_HT20_13], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_12],  16)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_7],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_6],   0)
    );

    /* 14 (LSB), 15, 20, 21 */
    OS_REG_WRITE(ah, 0xa3e4,
        POW_SM(p_pwr_array[ALL_TARGET_HT20_21], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_20],  16)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_15],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_14],   0)
    );

    /* Mixed HT20 and HT40 rates */
    /* HT20 22 (LSB), HT20 23, HT40 22, HT40 23 (MSB) */
    OS_REG_WRITE(ah, 0xa3e8,
        POW_SM(p_pwr_array[ALL_TARGET_HT40_23], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_22],  16)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_23],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_HT20_22],   0)
    );
    
    /* Write the HT40 power per rate set */
    /* correct PAR difference between HT40 and HT20/LEGACY */
    /* 0/8/16 (LSB), 1-3/9-11/17-19, 4, 5 (MSB) */
    OS_REG_WRITE(ah, 0xa3d8,
        POW_SM(p_pwr_array[ALL_TARGET_HT40_5], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_4],  16)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_1_3_9_11_17_19],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_0_8_16],   0)
    );

    /* 6 (LSB), 7, 12, 13 (MSB) */
    OS_REG_WRITE(ah, 0xa3dc,
        POW_SM(p_pwr_array[ALL_TARGET_HT40_13], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_12],  16)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_7], 8)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_6], 0)
    );

    /* 14 (LSB), 15, 20, 21 */
    OS_REG_WRITE(ah, 0xa3ec,
        POW_SM(p_pwr_array[ALL_TARGET_HT40_21], 24)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_20],  16)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_15],  8)
          | POW_SM(p_pwr_array[ALL_TARGET_HT40_14],   0)
    );

    return 0;
#undef POW_SM    
}