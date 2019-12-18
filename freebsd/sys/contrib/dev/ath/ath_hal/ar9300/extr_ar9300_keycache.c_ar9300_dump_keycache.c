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

/* Variables and functions */
 int AH_KEY_REG_SIZE ; 
 scalar_t__ AR_KEYTABLE_KEY0 (int) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,scalar_t__) ; 

void ar9300_dump_keycache(struct ath_hal *ah, int n, u_int32_t *entry)
{
#define AH_KEY_REG_SIZE	8
    int i;

    for (i = 0; i < AH_KEY_REG_SIZE; i++) {
        entry[i] = OS_REG_READ(ah, AR_KEYTABLE_KEY0(n) + i * 4);
    }
#undef AH_KEY_REG_SIZE
}