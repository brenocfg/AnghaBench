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
struct TYPE_2__ {scalar_t__ calibration_data_source; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 
 int ar9300_eeprom_size (struct ath_hal*) ; 
 int ar9300_otp_size (struct ath_hal*) ; 
 scalar_t__ calibration_data_otp ; 

int
ar9300_eeprom_base_address(struct ath_hal *ah)
{
    int size;

    if (AH9300(ah)->calibration_data_source == calibration_data_otp) {
		return ar9300_otp_size(ah)-1;
	}
	else
	{
		size = ar9300_eeprom_size(ah);
		if (size > 0) {
			return size - 1;
		} else {
			return ar9300_otp_size(ah)-1;
		}
	}
}