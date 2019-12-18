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
typedef  scalar_t__ u_int16_t ;
struct ath_hal {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ ar9300_eeprom_read_word (struct ath_hal*,int,scalar_t__*) ; 

int32_t 
ar9300_eeprom_size(struct ath_hal *ah)
{
    u_int16_t data;
    /*
     * first we'll try for 4096 bytes eeprom
     */
    if (ar9300_eeprom_read_word(ah, 2047, &data)) {
        if (data != 0) {
            return 4096;
        }
    }
    /*
     * then we'll try for 2048 bytes eeprom
     */
    if (ar9300_eeprom_read_word(ah, 1023, &data)) {
        if (data != 0) {
            return 2048;
        }
    }
    /*
     * then we'll try for 1024 bytes eeprom
     */
    if (ar9300_eeprom_read_word(ah, 511, &data)) {
        if (data != 0) {
            return 1024;
        }
    }
    return 0;
}