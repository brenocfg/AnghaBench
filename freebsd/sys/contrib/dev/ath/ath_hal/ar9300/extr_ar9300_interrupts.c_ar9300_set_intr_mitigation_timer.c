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
typedef  int HAL_INT_MITIGATION ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MIRT ; 
 int /*<<< orphan*/  AR_RIMT ; 
 int /*<<< orphan*/  AR_RIMT_FIRST ; 
 int /*<<< orphan*/  AR_RIMT_LAST ; 
 int /*<<< orphan*/  AR_TIMT ; 
 int /*<<< orphan*/  AR_TIMT_FIRST ; 
 int /*<<< orphan*/  AR_TIMT_LAST ; 
#define  HAL_INT_RX_FIRSTPKT 132 
#define  HAL_INT_RX_LASTPKT 131 
#define  HAL_INT_THRESHOLD 130 
#define  HAL_INT_TX_FIRSTPKT 129 
#define  HAL_INT_TX_LASTPKT 128 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar9300_set_intr_mitigation_timer(
    struct ath_hal* ah,
    HAL_INT_MITIGATION reg,
    u_int32_t value)
{
#ifdef AR5416_INT_MITIGATION
    switch (reg) {
    case HAL_INT_THRESHOLD:
        OS_REG_WRITE(ah, AR_MIRT, 0);
        break;
    case HAL_INT_RX_LASTPKT:
        OS_REG_RMW_FIELD(ah, AR_RIMT, AR_RIMT_LAST, value);
        break;
    case HAL_INT_RX_FIRSTPKT:
        OS_REG_RMW_FIELD(ah, AR_RIMT, AR_RIMT_FIRST, value);
        break;
    case HAL_INT_TX_LASTPKT:
        OS_REG_RMW_FIELD(ah, AR_TIMT, AR_TIMT_LAST, value);
        break;
    case HAL_INT_TX_FIRSTPKT:
        OS_REG_RMW_FIELD(ah, AR_TIMT, AR_TIMT_FIRST, value);
        break;
    default:
        break;
    }
#endif
}