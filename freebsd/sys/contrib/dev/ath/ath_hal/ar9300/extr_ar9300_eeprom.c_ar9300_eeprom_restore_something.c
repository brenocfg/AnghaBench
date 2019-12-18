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
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  ar9300_eeprom_t ;
struct TYPE_2__ {scalar_t__ calibration_data_source_address; void* calibration_data_source; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  Ar9300_eeprom_template_preference ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ar9300_eeprom_struct_default (int) ; 
 int /*<<< orphan*/ * ar9300_eeprom_struct_default_find_by_id (int /*<<< orphan*/ ) ; 
 int ar9300_eeprom_struct_default_many () ; 
 int /*<<< orphan*/  ar9300_eeprom_template_default ; 
 void* calibration_data_none ; 

__attribute__((used)) static int
ar9300_eeprom_restore_something(struct ath_hal *ah, ar9300_eeprom_t *mptr,
    int mdata_size)
{
    int it;
    ar9300_eeprom_t *dptr;
    int nptr;

    nptr = -1; 
    /*
     * if we didn't find any blocks in the memory,
     * put the prefered template in place
     */
    if (nptr < 0) {
        AH9300(ah)->calibration_data_source = calibration_data_none;
        AH9300(ah)->calibration_data_source_address = 0;
        dptr = ar9300_eeprom_struct_default_find_by_id(
            Ar9300_eeprom_template_preference);
        if (dptr != 0) {
            OS_MEMCPY(mptr, dptr, mdata_size);    
            nptr = 0;
        }
    }
    /*
     * if we didn't find the prefered one,
     * put the normal default template in place
     */
    if (nptr < 0) {
        AH9300(ah)->calibration_data_source = calibration_data_none;
        AH9300(ah)->calibration_data_source_address = 0;
        dptr = ar9300_eeprom_struct_default_find_by_id(
            ar9300_eeprom_template_default);
        if (dptr != 0) {
            OS_MEMCPY(mptr, dptr, mdata_size);    
            nptr = 0;
        }
    }
    /*
     * if we can't find the best template, put any old template in place
     * presume that newer ones are better, so search backwards
     */
    if (nptr < 0) {
        AH9300(ah)->calibration_data_source = calibration_data_none;
        AH9300(ah)->calibration_data_source_address = 0;
        for (it = ar9300_eeprom_struct_default_many() - 1; it >= 0; it--) {
            dptr = ar9300_eeprom_struct_default(it);
            if (dptr != 0) {
                OS_MEMCPY(mptr, dptr, mdata_size);    
                nptr = 0;
                break;
            }
        }
    }
    return nptr;
}