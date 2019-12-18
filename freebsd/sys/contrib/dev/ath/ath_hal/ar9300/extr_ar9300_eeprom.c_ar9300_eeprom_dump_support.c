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
typedef  int u_int ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  ar9300_eeprom_t ;
struct TYPE_2__ {int /*<<< orphan*/  ah_eeprom; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 

u_int
ar9300_eeprom_dump_support(struct ath_hal *ah, void **pp_e)
{
    *pp_e = &(AH9300(ah)->ah_eeprom);
    return sizeof(ar9300_eeprom_t);
}