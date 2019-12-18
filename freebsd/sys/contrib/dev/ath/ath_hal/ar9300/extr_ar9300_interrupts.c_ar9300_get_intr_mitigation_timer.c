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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
typedef  int HAL_INT_MITIGATION ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MIRT ; 
 int /*<<< orphan*/  AR_RIMT ; 
 int /*<<< orphan*/  AR_TIMT ; 
#define  HAL_INT_RX_FIRSTPKT 132 
#define  HAL_INT_RX_LASTPKT 131 
#define  HAL_INT_THRESHOLD 130 
#define  HAL_INT_TX_FIRSTPKT 129 
#define  HAL_INT_TX_LASTPKT 128 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

u_int32_t
ar9300_get_intr_mitigation_timer(struct ath_hal* ah, HAL_INT_MITIGATION reg)
{
    u_int32_t val = 0;
#ifdef AR5416_INT_MITIGATION
    switch (reg) {
    case HAL_INT_THRESHOLD:
        val = OS_REG_READ(ah, AR_MIRT);
        break;
    case HAL_INT_RX_LASTPKT:
        val = OS_REG_READ(ah, AR_RIMT) & 0xFFFF;
        break;
    case HAL_INT_RX_FIRSTPKT:
        val = OS_REG_READ(ah, AR_RIMT) >> 16;
        break;
    case HAL_INT_TX_LASTPKT:
        val = OS_REG_READ(ah, AR_TIMT) & 0xFFFF;
        break;
    case HAL_INT_TX_FIRSTPKT:
        val = OS_REG_READ(ah, AR_TIMT) >> 16;
        break;
    default:
        break;
    }
#endif
    return val;
}