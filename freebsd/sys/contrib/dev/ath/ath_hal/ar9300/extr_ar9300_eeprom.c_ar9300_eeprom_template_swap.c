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
typedef  int /*<<< orphan*/  ar9300_eeprom_t ;

/* Variables and functions */
 int ARRAY_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ar9300_eeprom_struct_default (int) ; 
 int /*<<< orphan*/  ar9300_swap_eeprom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default9300 ; 

void ar9300_eeprom_template_swap(void)
{
    int it;
    ar9300_eeprom_t *dptr;

    for (it = 0; it < ARRAY_LENGTH(default9300); it++) {
        dptr = ar9300_eeprom_struct_default(it);
        if (dptr != 0) {
            ar9300_swap_eeprom(dptr);
        }
    }
}