#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int template_version; } ;
typedef  TYPE_1__ ar9300_eeprom_t ;

/* Variables and functions */
 int ARRAY_LENGTH (TYPE_1__**) ; 
 TYPE_1__** default9300 ; 

ar9300_eeprom_t *
ar9300_eeprom_struct_default_find_by_id(int id) 
{
    int it;

    for (it = 0; it < ARRAY_LENGTH(default9300); it++) {
        if (default9300[it] != 0 && default9300[it]->template_version == id) {
            return default9300[it];
        }
    }
    return 0;
}