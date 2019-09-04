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
typedef  int uint32_t ;

/* Variables and functions */
 int** charset_translations ; 

uint32_t*
translation_table(uint32_t which) {
    switch(which){
        case 'B':
            return charset_translations[0];
        case '0':
            return charset_translations[1];
        case 'U':
            return charset_translations[2];
        case 'V':
            return charset_translations[3];
        case 'A':
            return charset_translations[4];
        default:
            return charset_translations[0];
    }
}