#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ctl_index_5g; int /*<<< orphan*/ * ctl_index_2g; } ;
struct ath_hal_9300 {TYPE_1__ ah_eeprom; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_1__ ar9300_eeprom_t ;
typedef  int /*<<< orphan*/  OSP_CAL_CTL_DATA_5G ;
typedef  int /*<<< orphan*/  OSP_CAL_CTL_DATA_2G ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int OSPREY_NUM_BAND_EDGES_2G ; 
 int OSPREY_NUM_BAND_EDGES_5G ; 
 int OSPREY_NUM_CTLS_2G ; 
 int OSPREY_NUM_CTLS_5G ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

HAL_BOOL
ar9300_set_ctl_pwr(struct ath_hal *ah, u_int8_t *ctl_array)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    ar9300_eeprom_t *p_eep_data = &ahp->ah_eeprom;
    u_int8_t *ctl_index;
    u_int32_t offset = 0;

    if (!ctl_array)
        return AH_FALSE;

    /* copy 2G ctl freqbin and power data */
    ctl_index = p_eep_data->ctl_index_2g;
    OS_MEMCPY(ctl_index + OSPREY_NUM_CTLS_2G, ctl_array,
                OSPREY_NUM_CTLS_2G * OSPREY_NUM_BAND_EDGES_2G +     /* ctl_freqbin_2G */
                OSPREY_NUM_CTLS_2G * sizeof(OSP_CAL_CTL_DATA_2G));  /* ctl_power_data_2g */
    offset = (OSPREY_NUM_CTLS_2G * OSPREY_NUM_BAND_EDGES_2G) +
            ( OSPREY_NUM_CTLS_2G * sizeof(OSP_CAL_CTL_DATA_2G));


    /* copy 2G ctl freqbin and power data */
    ctl_index = p_eep_data->ctl_index_5g;
    OS_MEMCPY(ctl_index + OSPREY_NUM_CTLS_5G, ctl_array + offset,
                OSPREY_NUM_CTLS_5G * OSPREY_NUM_BAND_EDGES_5G +     /* ctl_freqbin_5G */
                OSPREY_NUM_CTLS_5G * sizeof(OSP_CAL_CTL_DATA_5G));  /* ctl_power_data_5g */

    return AH_FALSE;
}