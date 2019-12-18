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
 int /*<<< orphan*/  AR_PCU_ALWAYS_PERFORM_KEYSEARCH ; 
 int /*<<< orphan*/  AR_PCU_MISC ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_enable_keysearch_always(struct ath_hal *ah, int enable)
{
    u_int32_t val;

    if (!ah) {
        return;
    }
    val = OS_REG_READ(ah, AR_PCU_MISC);
    if (enable) {
        val |= AR_PCU_ALWAYS_PERFORM_KEYSEARCH;
    } else {
        val &= ~AR_PCU_ALWAYS_PERFORM_KEYSEARCH;
    }
    OS_REG_WRITE(ah, AR_PCU_MISC, val);
}