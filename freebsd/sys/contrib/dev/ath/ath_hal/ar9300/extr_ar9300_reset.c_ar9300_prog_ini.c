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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal {int dummy; } ;
struct ar9300_ini_array {int ia_columns; int ia_rows; int /*<<< orphan*/ * ia_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  INI_RA (struct ar9300_ini_array*,int,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAR_6773 (int) ; 

__attribute__((used)) static inline void
ar9300_prog_ini(struct ath_hal *ah, struct ar9300_ini_array *ini_arr,
    int column)
{
    int i, reg_writes = 0;

    /* New INI format: Array may be undefined (pre, core, post arrays) */
    if (ini_arr->ia_array == NULL) {
        return;
    }

    /*
     * New INI format: Pre, core, and post arrays for a given subsystem may be
     * modal (> 2 columns) or non-modal (2 columns).
     * Determine if the array is non-modal and force the column to 1.
     */
    if (column >= ini_arr->ia_columns) {
        column = 1;
    }

    for (i = 0; i < ini_arr->ia_rows; i++) {
        u_int32_t reg = INI_RA(ini_arr, i, 0);
        u_int32_t val = INI_RA(ini_arr, i, column);

        /*
        ** Determine if this is a shift register value 
        ** (reg >= 0x16000 && reg < 0x17000 for Osprey) , 
        ** and insert the configured delay if so. 
        ** -this delay is not required for Osprey (EV#71410)
        */
        OS_REG_WRITE(ah, reg, val);
        WAR_6773(reg_writes);

    }
}