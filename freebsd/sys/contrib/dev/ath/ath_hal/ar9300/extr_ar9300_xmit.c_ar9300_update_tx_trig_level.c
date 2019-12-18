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
typedef  scalar_t__ u_int32_t ;
struct ath_hal_9300 {scalar_t__ ah_tx_trig_level; int ah_mask_reg; } ;
struct ath_hal {int dummy; } ;
typedef  int HAL_INT ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int AH_FALSE ; 
 scalar_t__ AR_FTRIG ; 
 int /*<<< orphan*/  AR_TXCFG ; 
 int HAL_INT_GLOBAL ; 
 scalar_t__ MAX_TX_FIFO_THRESHOLD ; 
 scalar_t__ MIN_TX_FIFO_THRESHOLD ; 
 scalar_t__ MS (scalar_t__,scalar_t__) ; 
 scalar_t__ OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SM (scalar_t__,scalar_t__) ; 
 int ar9300_set_interrupts (struct ath_hal*,int,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_update_tx_trig_level(struct ath_hal *ah, HAL_BOOL b_inc_trig_level)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    u_int32_t txcfg, cur_level, new_level;
    HAL_INT omask;

    if (AH9300(ah)->ah_tx_trig_level >= MAX_TX_FIFO_THRESHOLD &&
        b_inc_trig_level)
    {
        return AH_FALSE;
    }

    /*
     * Disable interrupts while futzing with the fifo level.
     */
    omask = ar9300_set_interrupts(ah, ahp->ah_mask_reg &~ HAL_INT_GLOBAL, 0);

    txcfg = OS_REG_READ(ah, AR_TXCFG);
    cur_level = MS(txcfg, AR_FTRIG);
    new_level = cur_level;

    if (b_inc_trig_level)  {   /* increase the trigger level */
        if (cur_level < MAX_TX_FIFO_THRESHOLD) {
            new_level++;
        }
    } else if (cur_level > MIN_TX_FIFO_THRESHOLD) {
        new_level--;
    }

    if (new_level != cur_level) {
        /* Update the trigger level */
        OS_REG_WRITE(ah,
            AR_TXCFG, (txcfg &~ AR_FTRIG) | SM(new_level, AR_FTRIG));
    }

    /* re-enable chip interrupts */
    ar9300_set_interrupts(ah, omask, 0);

    AH9300(ah)->ah_tx_trig_level = new_level;

    return (new_level != cur_level);
}