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
struct ath_hal_9300 {int /*<<< orphan*/  ah_eeprom; } ;
struct ath_hal {int dummy; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  ar9300_eeprom_t ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ar9300_eeprom_struct_default_find_by_id (int) ; 
 int ar9300_eeprom_struct_size () ; 
 int /*<<< orphan*/  calibration_data_none ; 
 int /*<<< orphan*/  calibration_data_source ; 
 scalar_t__ calibration_data_source_address ; 

int32_t ar9300_eeprom_template_install(struct ath_hal *ah, int32_t value)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    ar9300_eeprom_t *mptr, *dptr;
    int mdata_size;

    mptr = &ahp->ah_eeprom;
    mdata_size = ar9300_eeprom_struct_size();
    if (mptr != 0) {
#if 0
        calibration_data_source = calibration_data_none;
        calibration_data_source_address = 0;
#endif
        dptr = ar9300_eeprom_struct_default_find_by_id(value);
        if (dptr != 0) {
            OS_MEMCPY(mptr, dptr, mdata_size);
            return 0;
        }
    }
    return -1;
}